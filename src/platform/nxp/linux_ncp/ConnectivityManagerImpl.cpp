/*
 *
 *    Copyright (c) 2020-2022 Project CHIP Authors
 *    Copyright (c) 2019 Nest Labs, Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <platform/internal/CHIPDeviceLayerInternal.h>

#include <platform/CommissionableDataProvider.h>
#include <platform/ConnectivityManager.h>
#include <platform/DeviceControlServer.h>
#include <platform/DiagnosticDataProvider.h>
#include <platform/nxp/linux_ncp/ConnectivityUtils.h>
#include <platform/nxp/linux_ncp/DiagnosticDataProviderImpl.h>
#include <platform/Linux/NetworkCommissioningDriver.h>
#include <platform/Linux/WirelessDefs.h>
#include <platform/internal/BLEManager.h>

#include <algorithm>
#include <cstdlib>
#include <new>
#include <string>
#include <utility>
#include <vector>

#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <lib/support/BytesToHex.h>
#include <lib/support/CHIPMemString.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/logging/CHIPLogging.h>

#include <platform/internal/GenericConnectivityManagerImpl_UDP.ipp>

#if INET_CONFIG_ENABLE_TCP_ENDPOINT
#include <platform/internal/GenericConnectivityManagerImpl_TCP.ipp>
#endif

#if CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE
#include <platform/internal/GenericConnectivityManagerImpl_BLE.ipp>
#endif

#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
#include <platform/internal/GenericConnectivityManagerImpl_Thread.ipp>
#endif

#if CHIP_DEVICE_CONFIG_ENABLE_WPA
#include <credentials/CHIPCert.h>
#include <platform/GLibTypeDeleter.h>
#include <platform/internal/GenericConnectivityManagerImpl_WiFi.ipp>
#endif

extern "C" {
#include "ncp_wifi_api.h"
#include "ncp_host_app.h"
}

using namespace ::chip;
using namespace ::chip::TLV;
using namespace ::chip::Credentials;
using namespace ::chip::DeviceLayer;
using namespace ::chip::DeviceLayer::Internal;
using namespace ::chip::app::Clusters::GeneralDiagnostics;
using namespace ::chip::app::Clusters::WiFiNetworkDiagnostics;

using namespace ::chip::DeviceLayer::NetworkCommissioning;

namespace chip {

namespace DeviceLayer {

// Configured SSID
uint8_t ConnectivityManagerImpl::sCfgSSID[Internal::kMaxWiFiSSIDLength];
uint8_t ConnectivityManagerImpl::sCfgSSIDLen;

ConnectivityManagerImpl ConnectivityManagerImpl::sInstance;

CHIP_ERROR ConnectivityManagerImpl::_Init()
{
#if CHIP_DEVICE_CONFIG_ENABLE_WPA
    mWiFiStationMode              = kWiFiStationMode_Disabled;
    mWiFiStationReconnectInterval = System::Clock::Milliseconds32(CHIP_DEVICE_CONFIG_WIFI_STATION_RECONNECT_INTERVAL);
#endif
    mpConnectCallback = nullptr;
    mpScanCallback    = nullptr;

    /* Initialize ncp host */
    ncp_host_main();

    if (ConnectivityUtils::GetEthInterfaceName(mEthIfName, IFNAMSIZ) == CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "Got Ethernet interface: %s", mEthIfName);
    }
    else
    {
        ChipLogError(DeviceLayer, "Failed to get Ethernet interface");
        mEthIfName[0] = '\0';
    }

    // Initialize the generic base classes that require it.
#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
    GenericConnectivityManagerImpl_Thread<ConnectivityManagerImpl>::_Init();
#endif

#if CHIP_DEVICE_CONFIG_ENABLE_WIFI
    if (ConnectivityUtils::GetWiFiInterfaceName(sWiFiIfName, IFNAMSIZ) == CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "Got WiFi interface: %s", sWiFiIfName);
    }
    else
    {
        ChipLogError(DeviceLayer, "Failed to get WiFi interface");
        sWiFiIfName[0] = '\0';
    }

    if (GetDiagnosticDataProvider().ResetWiFiNetworkDiagnosticsCounts() != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "Failed to reset WiFi statistic counts");
    }
#endif

    return CHIP_NO_ERROR;
}

void ConnectivityManagerImpl::_OnPlatformEvent(const ChipDeviceEvent * event)
{
    // Forward the event to the generic base classes as needed.
#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
    GenericConnectivityManagerImpl_Thread<ConnectivityManagerImpl>::_OnPlatformEvent(event);
#endif
}

#if CHIP_DEVICE_CONFIG_ENABLE_WPA

ConnectivityManager::WiFiStationMode ConnectivityManagerImpl::_GetWiFiStationMode()
{
    if (mWiFiStationMode != kWiFiStationMode_ApplicationControlled)
    {
        mWiFiStationMode =
            kWiFiStationMode_Enabled; //(mWpaSupplicant.iface != nullptr) ? kWiFiStationMode_Enabled : kWiFiStationMode_Disabled;
    }

    return mWiFiStationMode;
}

CHIP_ERROR ConnectivityManagerImpl::_SetWiFiStationMode(ConnectivityManager::WiFiStationMode val)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    VerifyOrExit(val != ConnectivityManager::kWiFiStationMode_NotSupported, err = CHIP_ERROR_INVALID_ARGUMENT);

    if (mWiFiStationMode != val)
    {
        ChipLogProgress(DeviceLayer, "WiFi station mode change: %s -> %s", WiFiStationModeToStr(mWiFiStationMode),
                        WiFiStationModeToStr(val));
    }

    mWiFiStationMode = val;
exit:
    return err;
}

System::Clock::Timeout ConnectivityManagerImpl::_GetWiFiStationReconnectInterval()
{
    return mWiFiStationReconnectInterval;
}

CHIP_ERROR ConnectivityManagerImpl::_SetWiFiStationReconnectInterval(System::Clock::Timeout val)
{
    mWiFiStationReconnectInterval = val;

    return CHIP_NO_ERROR;
}

bool ConnectivityManagerImpl::_IsWiFiStationEnabled()
{
    return GetWiFiStationMode() == kWiFiStationMode_Enabled;
}

bool ConnectivityManagerImpl::_IsWiFiStationConnected()
{
    bool ret            = false;
    char * state = nullptr;

    ChipLogProgress(DeviceLayer, "[ncp-host] Get ncp connect state.\r\n");

    state = wlan_ncp_get_state();

    if (g_strcmp0(state, "completed") == 0)
    {
        mConnectivityFlag.Set(ConnectivityFlags::kHaveIPv4InternetConnectivity)
            .Set(ConnectivityFlags::kHaveIPv6InternetConnectivity);
        ret = true;
    }
    
    return ret;
}

bool ConnectivityManagerImpl::_IsWiFiStationApplicationControlled()
{
    return mWiFiStationMode == ConnectivityManager::kWiFiStationMode_ApplicationControlled;
}

bool ConnectivityManagerImpl::_IsWiFiStationProvisioned()
{
    bool ret          = false;
    NCP_WLAN_NETWORK * sta_network = NULL;

    ChipLogProgress(DeviceLayer, "[ncp-host] Get current network.\r\n");
    ret = wlan_ncp_get_current_network(sta_network);

    if(sta_network->ssid != NULL)
    {
        ret = true;
    }

    return ret;
}

void ConnectivityManagerImpl::_ClearWiFiStationProvision()
{
    bool ret = true;
    if (mWiFiStationMode != kWiFiStationMode_ApplicationControlled)
    {
        ChipLogProgress(DeviceLayer, "[ncp-host] remove all networks. ");

        ret = wlan_ncp_remove_all_networks();

        if (ret != true)
        {
            ChipLogProgress(DeviceLayer, "failed to remove all networks ");
        }
    }

}

bool ConnectivityManagerImpl::_CanStartWiFiScan()
{
    bool ret = true;
    return ret;
}

void ConnectivityManagerImpl::StartWiFiManagement()
{
    //call wlan_start(), do not need at ncp host side
}

bool ConnectivityManagerImpl::IsWiFiManagementStarted()
{
    bool ret = true;
    return ret;
}

void ConnectivityManagerImpl::StartNonConcurrentWiFiManagement()
{
    StartWiFiManagement();

    for (int cnt = 0; cnt < WIFI_START_CHECK_ATTEMPTS; cnt++)
    {
        if (IsWiFiManagementStarted())
        {
            DeviceControlServer::DeviceControlSvr().PostOperationalNetworkStartedEvent();
            ChipLogProgress(DeviceLayer, "Non-concurrent mode Wi-Fi Management Started.");
            return;
        }
        usleep(WIFI_START_CHECK_TIME_USEC);
    }
    ChipLogError(Ble, "Non-concurrent mode Wi-Fi Management taking too long to start.");
}

CHIP_ERROR
ConnectivityManagerImpl::_ConnectWiFiNetworkAsync(GVariant * args,
                                                  NetworkCommissioning::Internal::WirelessDriver::ConnectCallback * apCallback)
{
    GAutoPtr<GVariant> argsDeleter(g_variant_ref_sink(args)); // args may be floating, ensure we don't leak it

    CHIP_ERROR ret = CHIP_NO_ERROR;
    GAutoPtr<GError> err;
    gboolean result;
    NCP_WLAN_NETWORK sta_network;

    if (!wlan_ncp_scan())
    {
        ChipLogProgress(DeviceLayer, "Error: scan request failed");
        ret = CHIP_ERROR_INTERNAL;
    }

    if (wlan_ncp_get_current_network(&sta_network) == WM_SUCCESS)
    {
        GAutoPtr<GError> error;

        result = wlan_ncp_remove_network(&sta_network);

        if (result)
        {
            ChipLogProgress(DeviceLayer, "removed network name: %s", sta_network.name);
        }
        else
        {
            ChipLogProgress(DeviceLayer, "failed to stop AP mode");
            ret = CHIP_ERROR_INTERNAL;
        }

        SuccessOrExit(ret);
    }

    char * ssid;
    int8_t mode;
    int8_t frequency;
    char * network_name;
    char * key;
    int8_t key_len;

    g_variant_lookup(args, "ssid", "s", &ssid);
    g_variant_lookup(args, "mode", "i", &mode);
    g_variant_lookup(args, "frequency", "i", &frequency);
    g_variant_lookup(args, "network_name", "s", &network_name);
    g_variant_lookup(args, "key", "s", &key);
    g_variant_lookup(args, "key_len", "i", &key_len);

    (void) memcpy(&sta_network.name, network_name, strlen(network_name) + 1);

    ChipLogProgress(DeviceLayer, "[ncp-host] remove network name %s.", network_name);
    
    wlan_ncp_remove_network(&sta_network);
    result = wlan_ncp_add_network(ssid, key, mode, frequency, network_name, key_len);

    if (result)
    {
        ChipLogProgress(DeviceLayer, "added network: %s", network_name);
        wlan_ncp_disconnect();
        ChipLogProgress(DeviceLayer, "[ncp-host] do connect with network name %s.", network_name);
        wlan_ncp_connect(network_name);
        mpConnectCallback = apCallback;
        
        if(mpConnectCallback != nullptr)
        {
            ChipLogProgress(DeviceLayer, "xinyutest onreselt send event kOperationalNetworkEnabled\r\n");
            mpConnectCallback->OnResult(Status::kSuccess, CharSpan(), 0);
            mpConnectCallback = nullptr;
        }
    }
    else
    {
        ChipLogError(DeviceLayer, "failed to add network");
        ret = CHIP_ERROR_INTERNAL;
    }

exit:
    return ret;
}

CHIP_ERROR
ConnectivityManagerImpl::ConnectWiFiNetworkAsync(ByteSpan ssid, ByteSpan credentials,
                                                 NetworkCommissioning::Internal::WirelessDriver::ConnectCallback * connectCallback)
{
    char ssidStr[kMaxWiFiSSIDLength + 1] = { 0 };
    char keyStr[kMaxWiFiKeyLength + 1]   = { 0 };

    VerifyOrReturnError(ssid.size() <= kMaxWiFiSSIDLength, CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(credentials.size() <= kMaxWiFiKeyLength, CHIP_ERROR_INVALID_ARGUMENT);

    // There is another ongoing connect request, reject the new one.
    VerifyOrReturnError(mpConnectCallback == nullptr, CHIP_ERROR_INCORRECT_STATE);

    GVariantBuilder builder;
    g_variant_builder_init(&builder, G_VARIANT_TYPE_VARDICT);
    memcpy(ssidStr, ssid.data(), ssid.size());
    memcpy(keyStr, credentials.data(), credentials.size());

    memcpy(sCfgSSID, ssidStr, ssid.size());
    sCfgSSIDLen = ssid.size();

    if(credentials.size() > 0)
    {
        g_variant_builder_add(&builder, "{sv}", "key_mgmt", g_variant_new_int32(WLAN_SECURITY_WILDCARD));
    }
    else
    {
        g_variant_builder_add(&builder, "{sv}", "key_mgmt", g_variant_new_int32(WLAN_SECURITY_NONE));
    }
    g_variant_builder_add(&builder, "{sv}", "ssid", g_variant_new_string(ssidStr));
    g_variant_builder_add(&builder, "{sv}", "key", g_variant_new_string(keyStr));
    g_variant_builder_add(&builder, "{sv}", "network_name", g_variant_new_string("MATTER-NCP-STA"));
    g_variant_builder_add(&builder, "{sv}", "key_len", g_variant_new_int32(credentials.size()));
    GVariant * args = g_variant_builder_end(&builder);

    return _ConnectWiFiNetworkAsync(args, connectCallback);
}

CHIP_ERROR ConnectivityManagerImpl::CommitConfig()
{
    return CHIP_NO_ERROR;
}

CHIP_ERROR ConnectivityManagerImpl::GetWiFiBssId(MutableByteSpan & value)
{
    constexpr size_t bssIdSize = 6;
    NCP_WLAN_NETWORK sta_network;
    VerifyOrReturnError(value.size() >= bssIdSize, CHIP_ERROR_BUFFER_TOO_SMALL);

    int ret = wlan_ncp_get_current_network(&sta_network);

    if (ret != WM_SUCCESS)
    {
        ChipLogProgress(DeviceLayer, "GetWiFiBssId failed: %d", ret);
        return CHIP_ERROR_READ_FAILED;
    }

    memcpy(value.data(), sta_network.bssid, bssIdSize);
    value.reduce_size(bssIdSize);

    ChipLogProgress(DeviceLayer, "GetWiFiBssId: %02x:%02x:%02x:%02x:%02x:%02x", value.data()[0], value.data()[1], value.data()[2],
                    value.data()[3], value.data()[4], value.data()[5]);
    return CHIP_NO_ERROR;
}

CHIP_ERROR ConnectivityManagerImpl::GetWiFiSecurityType(SecurityTypeEnum & securityType)
{
    NCP_WLAN_NETWORK sta_network;
    int ret = wlan_ncp_get_current_network(&sta_network);
    if (ret != WM_SUCCESS)
    {
        // Set as no security by default
        securityType = SecurityTypeEnum::kNone;
        return CHIP_NO_ERROR;
    }
    switch (sta_network.security_type)
    {
    case WLAN_SECURITY_WEP_OPEN:
    case WLAN_SECURITY_WEP_SHARED:
        securityType = SecurityTypeEnum::kWep;
        break;
    case WLAN_SECURITY_WPA:
        securityType = SecurityTypeEnum::kWpa;
        break;
    case WLAN_SECURITY_WPA2:
        securityType = SecurityTypeEnum::kWpa2;
        break;
    case WLAN_SECURITY_WPA3_SAE:
        securityType = SecurityTypeEnum::kWpa3;
        break;
    case WLAN_SECURITY_NONE:
    default: // Default: No_security
        securityType = SecurityTypeEnum::kNone;
    }

    ChipLogProgress(DeviceLayer, "GetWiFiSecurityType: %u", to_underlying(securityType));
    return CHIP_NO_ERROR;
}

CHIP_ERROR ConnectivityManagerImpl::GetWiFiVersion(WiFiVersionEnum & wiFiVersion)
{
    // We don't have direct API to get the WiFi version yet, return 802.11n on Linux simulation.
    wiFiVersion = WiFiVersionEnum::kN;

    return CHIP_NO_ERROR;
}

int32_t ConnectivityManagerImpl::GetDisconnectReason()
{
    return 1;
}

CHIP_ERROR ConnectivityManagerImpl::GetConfiguredNetwork(NetworkCommissioning::Network & network)
{
    network.connected = true;
    memcpy(network.networkID, sCfgSSID, sCfgSSIDLen);
    network.networkIDLen = sCfgSSIDLen;

    ChipLogDetail(DeviceLayer, "Current connected network: (ToDo)");
    return CHIP_NO_ERROR;
}

CHIP_ERROR ConnectivityManagerImpl::StartWiFiScan(ByteSpan ssid, WiFiDriver::ScanCallback * callback)
{
    // There is another ongoing scan request, reject the new one.
    // ====> Do it after scan is implemented (ToDo)
    VerifyOrReturnError(mpScanCallback == nullptr, CHIP_ERROR_INCORRECT_STATE);
    VerifyOrReturnError(ssid.size() <= sizeof(sInterestedSSID), CHIP_ERROR_INVALID_ARGUMENT);
    uint8_t count = 0;

    CHIP_ERROR ret = CHIP_NO_ERROR;
    memset(sInterestedSSID, 0, sizeof(sInterestedSSID));
    memcpy(sInterestedSSID, ssid.data(), ssid.size());
    sInterestedSSIDLen = ssid.size();

    ChipLogProgress(DeviceLayer, "[ncp-host] initialized network scan. %u, [%s]", sInterestedSSIDLen, sInterestedSSID);
    mpScanCallback = callback;

    // Do Scan
    if (!wlan_ncp_scan())
    {
        ChipLogProgress(DeviceLayer, "Error: scan request failed");
    }
    else
    {
        ChipLogProgress(DeviceLayer, "Scan scheduled now...");
    }

    ChipLogProgress(DeviceLayer, "[ncp-host] initialized network scan. ");

    wlan_ncp_get_scan_result_count(&count); 

    ConnectivityManagerImpl()._OnWpaInterfaceScanDone(count);

    return ret;
}

namespace {
std::pair<WiFiBand, uint16_t> GetBandAndChannelFromFrequency(uint32_t freq)
{
    std::pair<WiFiBand, uint16_t> ret = std::make_pair(WiFiBand::k2g4, 0);
    if (freq <= 931)
    {
        ret.first = WiFiBand::k1g;
        if (freq >= 916)
        {
            ret.second = ((freq - 916) * 2) - 1;
        }
        else if (freq >= 902)
        {
            ret.second = (freq - 902) * 2;
        }
        else if (freq >= 863)
        {
            ret.second = (freq - 863) * 2;
        }
        else
        {
            ret.second = 1;
        }
    }
    else if (freq <= 2472)
    {
        ret.second = static_cast<uint16_t>((freq - 2412) / 5 + 1);
    }
    else if (freq == 2484)
    {
        ret.second = 14;
    }
    else if (freq >= 3600 && freq <= 3700)
    {
        // Note: There are not many devices supports this band, and this band contains rational frequency in MHz, need to figure out
        // the behavior of wpa_supplicant in this case.
        ret.first = WiFiBand::k3g65;
    }
    else if (freq >= 5035 && freq <= 5945)
    {
        ret.first  = WiFiBand::k5g;
        ret.second = static_cast<uint16_t>((freq - 5000) / 5);
    }
    else if (freq == 5960 || freq == 5980)
    {
        ret.first  = WiFiBand::k5g;
        ret.second = static_cast<uint16_t>((freq - 5000) / 5);
    }
    else if (freq >= 5955)
    {
        ret.first  = WiFiBand::k6g;
        ret.second = static_cast<uint16_t>((freq - 5950) / 5);
    }
    else if (freq >= 58000)
    {
        ret.first = WiFiBand::k60g;
        // Note: Some channel has the same center frequency but different bandwidth. Should figure out wpa_supplicant's behavior in
        // this case. Also, wpa_supplicant's frequency property is uint16 infact.
        switch (freq)
        {
        case 58'320:
            ret.second = 1;
            break;
        case 60'480:
            ret.second = 2;
            break;
        case 62'640:
            ret.second = 3;
            break;
        case 64'800:
            ret.second = 4;
            break;
        case 66'960:
            ret.second = 5;
            break;
        case 69'120:
            ret.second = 6;
            break;
        case 59'400:
            ret.second = 9;
            break;
        case 61'560:
            ret.second = 10;
            break;
        case 63'720:
            ret.second = 11;
            break;
        case 65'880:
            ret.second = 12;
            break;
        case 68'040:
            ret.second = 13;
            break;
        }
    }
    return ret;
}

} // namespace

bool ConnectivityManagerImpl::_GetBssInfo(const uint8_t sid, NetworkCommissioning::WiFiScanResponse & result)
{
    NCP_WLAN_SCAN_RESULT res;
    int err;
    err = wlan_ncp_get_scan_result(sid, &res);
    if (err)
    {
        ChipLogProgress(DeviceLayer, "Error: can't get scan res %d", sid);
        return false;
    }
    // => ssid
    memset(result.ssid, 0, sizeof(result.ssid));
    result.ssidLen = strlen(res.ssid);
    memcpy(result.ssid, res.ssid, result.ssidLen);
    // => bssid
    memcpy(result.bssid, res.bssid, kWiFiBSSIDLength);
    // => rssi
    result.rssi = static_cast<int8_t>(0 - res.rssi);
    // => band, mw320 only works in 2.4G
    result.wiFiBand = app::Clusters::NetworkCommissioning::WiFiBandEnum::k2g4;
    // => channel
    result.channel = res.channel;
    // => security
    if (res.wep)
    {
        result.security.Set(WiFiSecurity::kWep);
    }
    else if (res.wpa)
    {
        result.security.Set(WiFiSecurity::kWpaPersonal);
    }
    else if ((res.wpa2) || (res.wpa2_entp))
    {
        result.security.Set(WiFiSecurity::kWpa2Personal);
    }
    else if (res.wpa3_sae)
    {
        result.security.Set(WiFiSecurity::kWpa3Personal);
    }
    else
    {
        result.security.Set(WiFiSecurity::kUnencrypted);
    }

    return true;
}

void ConnectivityManagerImpl::_OnWpaInterfaceScanDone(unsigned int count)
{
    ChipLogProgress(DeviceLayer, "network scan done (%d)", count);
    // No ap reported
    if (count == 0)
    {
        ChipLogProgress(DeviceLayer, "wpa_supplicant: no network found");
        DeviceLayer::SystemLayer().ScheduleLambda([this]() {
            if (mpScanCallback != nullptr)
            {
                mpScanCallback->OnFinished(Status::kSuccess, CharSpan(), nullptr);
                mpScanCallback = nullptr;
            }
        });
        return;
    }

    // Get the scan result from SDK and push to the list
    std::vector<WiFiScanResponse> * networkScanned = new std::vector<WiFiScanResponse>();
    for (uint8_t id = 0; id < count; id++)
    {
        WiFiScanResponse network;
        if (_GetBssInfo(id, network))
        {
            if (sInterestedSSIDLen == 0)
            {
                networkScanned->push_back(network);
            }
            else if (network.ssidLen == sInterestedSSIDLen && memcmp(network.ssid, sInterestedSSID, sInterestedSSIDLen) == 0)
            {
                networkScanned->push_back(network);
            }
        }
    }

    DeviceLayer::SystemLayer().ScheduleLambda([this, networkScanned]() {
        // Note: We cannot post a event in ScheduleLambda since std::vector is not trivial copiable. This results in the use of
        // const_cast but should be fine for almost all cases, since we actually handled the ownership of this element to this
        // lambda.
        if (mpScanCallback != nullptr)
        {
            LinuxScanResponseIterator<WiFiScanResponse> iter(const_cast<std::vector<WiFiScanResponse> *>(networkScanned));
            mpScanCallback->OnFinished(Status::kSuccess, CharSpan(), &iter);
            mpScanCallback = nullptr;
        }

        delete const_cast<std::vector<WiFiScanResponse> *>(networkScanned);
    });
}
#endif // CHIP_DEVICE_CONFIG_ENABLE_WPA

} // namespace DeviceLayer
} // namespace chip
