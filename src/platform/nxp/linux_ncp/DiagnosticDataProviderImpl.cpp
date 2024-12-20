/*
 *
 *    Copyright (c) 2021-2022 Project CHIP Authors
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

/**
 *    @file
 *          Provides an implementation of the DiagnosticDataProvider object
 *          for Linux platform.
 */

#include <platform/internal/CHIPDeviceLayerInternal.h>

#include <app/data-model/List.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/CHIPMemString.h>
#include <lib/support/logging/CHIPLogging.h>
#include <platform/DiagnosticDataProvider.h>
#include <platform/nxp/linux_ncp/ConnectivityUtils.h>
#include <platform/nxp/linux_ncp/DiagnosticDataProviderImpl.h>

#include <arpa/inet.h>
#include <dirent.h>
#include <ifaddrs.h>
#include <linux/ethtool.h>
#include <linux/if_link.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <malloc.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" {
#include "ncp_wifi_api.h"
}

using namespace ::chip;
using namespace ::chip::app;
using namespace ::chip::TLV;
using namespace ::chip::DeviceLayer;
using namespace ::chip::DeviceLayer::Internal;
using namespace ::chip::app::Clusters::GeneralDiagnostics;

namespace {

enum class EthernetStatsCountType
{
    kEthPacketRxCount,
    kEthPacketTxCount,
    kEthTxErrCount,
    kEthCollisionCount,
    kEthOverrunCount
};

enum class WiFiStatsCountType
{
    kWiFiUnicastPacketRxCount,
    kWiFiUnicastPacketTxCount,
    kWiFiMulticastPacketRxCount,
    kWiFiMulticastPacketTxCount,
    kWiFiOverrunCount
};

} // namespace

namespace chip {
namespace DeviceLayer {

DiagnosticDataProviderImpl & DiagnosticDataProviderImpl::GetDefaultInstance()
{
    static DiagnosticDataProviderImpl sInstance;
    return sInstance;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetCurrentHeapFree(uint64_t & currentHeapFree)
{
#ifndef __GLIBC__
    return CHIP_ERROR_NOT_IMPLEMENTED;
#else
    struct mallinfo mallocInfo = mallinfo();

    // Get the current amount of heap memory, in bytes, that are not being utilized
    // by the current running program.
    currentHeapFree = mallocInfo.fordblks;

    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DiagnosticDataProviderImpl::GetCurrentHeapUsed(uint64_t & currentHeapUsed)
{
#ifndef __GLIBC__
    return CHIP_ERROR_NOT_IMPLEMENTED;
#else
    struct mallinfo mallocInfo = mallinfo();

    // Get the current amount of heap memory, in bytes, that are being used by
    // the current running program.
    currentHeapUsed = mallocInfo.uordblks;

    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DiagnosticDataProviderImpl::GetCurrentHeapHighWatermark(uint64_t & currentHeapHighWatermark)
{
#ifndef __GLIBC__
    return CHIP_ERROR_NOT_IMPLEMENTED;
#else
    struct mallinfo mallocInfo = mallinfo();

    // The usecase of this function is embedded devices,on which we would need to intercept
    // malloc/calloc/free and then record the maximum amount of heap memory,in bytes, that
    // has been used by the Node.
    // On Linux, since it uses virtual memory, whereby a page of memory could be copied to
    // the hard disk, called swap space, and free up that page of memory. So it is impossible
    // to know accurately peak physical memory it use. We just return the current heap memory
    // being used by the current running program.
    currentHeapHighWatermark = mallocInfo.uordblks;

    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DiagnosticDataProviderImpl::ResetWatermarks()
{
    // If implemented, the server SHALL set the value of the CurrentHeapHighWatermark attribute to the
    // value of the CurrentHeapUsed.

    // On Linux, the write operation is non-op since we always rely on the mallinfo system
    // function to get the current heap memory.

    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetThreadMetrics(ThreadMetrics ** threadMetricsOut)
{
    CHIP_ERROR err = CHIP_ERROR_READ_FAILED;
    DIR * proc_dir = opendir("/proc/self/task");

    if (proc_dir == nullptr)
    {
        ChipLogError(DeviceLayer, "Failed to open current process task directory");
    }
    else
    {
        ThreadMetrics * head = nullptr;
        struct dirent * entry;

        /* proc available, iterate through tasks... */
        while ((entry = readdir(proc_dir)) != nullptr)
        {
            if (entry->d_name[0] == '.')
                continue;

            ThreadMetrics * thread = new ThreadMetrics();

            Platform::CopyString(thread->NameBuf, entry->d_name);
            thread->name.Emplace(CharSpan::fromCharString(thread->NameBuf));
            thread->id = atoi(entry->d_name);

            // TODO: Get stack info of each thread: thread->stackFreeCurrent,
            // thread->stackFreeMinimum, thread->stackSize.

            thread->Next = head;
            head         = thread;
        }

        closedir(proc_dir);

        *threadMetricsOut = head;
        err               = CHIP_NO_ERROR;
    }

    return err;
}

void DiagnosticDataProviderImpl::ReleaseThreadMetrics(ThreadMetrics * threadMetrics)
{
    while (threadMetrics)
    {
        ThreadMetrics * del = threadMetrics;
        threadMetrics       = threadMetrics->Next;
        delete del;
    }
}

CHIP_ERROR DiagnosticDataProviderImpl::GetRebootCount(uint16_t & rebootCount)
{
    uint32_t count = 0;

    CHIP_ERROR err = ConfigurationMgr().GetRebootCount(count);

    if (err == CHIP_NO_ERROR)
    {
        VerifyOrReturnError(count <= UINT16_MAX, CHIP_ERROR_INVALID_INTEGER_VALUE);
        rebootCount = static_cast<uint16_t>(count);
    }

    return err;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetUpTime(uint64_t & upTime)
{
    System::Clock::Timestamp currentTime = System::SystemClock().GetMonotonicTimestamp();
    System::Clock::Timestamp startTime   = PlatformMgrImpl().GetStartTime();

    if (currentTime >= startTime)
    {
        upTime = std::chrono::duration_cast<System::Clock::Seconds64>(currentTime - startTime).count();
        return CHIP_NO_ERROR;
    }

    return CHIP_ERROR_INVALID_TIME;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetTotalOperationalHours(uint32_t & totalOperationalHours)
{
    uint64_t upTime = 0;

    if (GetUpTime(upTime) == CHIP_NO_ERROR)
    {
        uint32_t totalHours = 0;
        if (ConfigurationMgr().GetTotalOperationalHours(totalHours) == CHIP_NO_ERROR)
        {
            VerifyOrReturnError(upTime / 3600 <= UINT32_MAX, CHIP_ERROR_INVALID_INTEGER_VALUE);
            totalOperationalHours = totalHours + static_cast<uint32_t>(upTime / 3600);
            return CHIP_NO_ERROR;
        }
    }

    return CHIP_ERROR_INVALID_TIME;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetBootReason(BootReasonType & bootReason)
{
    uint32_t reason = 0;

    CHIP_ERROR err = ConfigurationMgr().GetBootReason(reason);

    if (err == CHIP_NO_ERROR)
    {
        VerifyOrReturnError(reason <= UINT8_MAX, CHIP_ERROR_INVALID_INTEGER_VALUE);
        bootReason = static_cast<BootReasonType>(reason);
    }

    return err;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetActiveHardwareFaults(GeneralFaults<kMaxHardwareFaults> & hardwareFaults)
{
#if CHIP_CONFIG_TEST
    // On Linux Simulation, set following hardware faults statically.
    ReturnErrorOnFailure(hardwareFaults.add(to_underlying(HardwareFaultEnum::kRadio)));
    ReturnErrorOnFailure(hardwareFaults.add(to_underlying(HardwareFaultEnum::kSensor)));
    ReturnErrorOnFailure(hardwareFaults.add(to_underlying(HardwareFaultEnum::kPowerSource)));
    ReturnErrorOnFailure(hardwareFaults.add(to_underlying(HardwareFaultEnum::kUserInterfaceFault)));
#endif

    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetActiveRadioFaults(GeneralFaults<kMaxRadioFaults> & radioFaults)
{
#if CHIP_CONFIG_TEST
    // On Linux Simulation, set following radio faults statically.
    ReturnErrorOnFailure(radioFaults.add(to_underlying(RadioFaultEnum::kWiFiFault)));
    ReturnErrorOnFailure(radioFaults.add(to_underlying(RadioFaultEnum::kCellularFault)));
    ReturnErrorOnFailure(radioFaults.add(to_underlying(RadioFaultEnum::kThreadFault)));
    ReturnErrorOnFailure(radioFaults.add(to_underlying(RadioFaultEnum::kNFCFault)));
#endif

    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetActiveNetworkFaults(GeneralFaults<kMaxNetworkFaults> & networkFaults)
{
#if CHIP_CONFIG_TEST
    // On Linux Simulation, set following radio faults statically.
    ReturnErrorOnFailure(networkFaults.add(to_underlying(NetworkFaultEnum::kHardwareFailure)));
    ReturnErrorOnFailure(networkFaults.add(to_underlying(NetworkFaultEnum::kNetworkJammed)));
    ReturnErrorOnFailure(networkFaults.add(to_underlying(NetworkFaultEnum::kConnectionFailed)));
#endif

    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetNetworkInterfaces(NetworkInterface ** netifpp)
{
    NetworkInterface * ifp = new NetworkInterface();
    uint8_t size           = 0;

    strncpy(ifp->Name, "mlan0", Inet::InterfaceId::kMaxIfNameLength);
    ifp->Name[Inet::InterfaceId::kMaxIfNameLength - 1] = '\0';
    ifp->name                                          = CharSpan::fromCharString(ifp->Name);
    ifp->isOperational                                 = true;
    ifp->type                                          = app::Clusters::GeneralDiagnostics::InterfaceTypeEnum::kWiFi;
    ifp->offPremiseServicesReachableIPv4.SetNull();
    ifp->offPremiseServicesReachableIPv6.SetNull();
    if (ConnectivityUtils::GetInterfaceIPv4Addrs("", size, ifp) == CHIP_NO_ERROR)
    {
        if (size > 0)
        {
            ifp->IPv4Addresses = DataModel::List<const chip::ByteSpan>(ifp->Ipv4AddressSpans, size);
        }
    }
    if (ConnectivityUtils::GetInterfaceIPv6Addrs("", size, ifp) == CHIP_NO_ERROR)
    {
        if (size > 0)
        {
            ifp->IPv6Addresses = DataModel::List<const chip::ByteSpan>(ifp->Ipv6AddressSpans, size);
        }
    }
    ifp->Next = nullptr;
    *netifpp  = ifp;

    return CHIP_NO_ERROR;
}

void DiagnosticDataProviderImpl::ReleaseNetworkInterfaces(NetworkInterface * netifp)
{
    while (netifp)
    {
        NetworkInterface * del = netifp;
        netifp                 = netifp->Next;
        delete del;
    }
}

#if CHIP_DEVICE_CONFIG_ENABLE_WIFI
CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiChannelNumber(uint16_t & channelNumber)
{
    if (ConnectivityMgrImpl().GetWiFiIfName() == nullptr)
    {
        return CHIP_ERROR_READ_FAILED;
    }

    return ConnectivityUtils::GetWiFiChannelNumber(ConnectivityMgrImpl().GetWiFiIfName(), channelNumber);
}

CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiRssi(int8_t & rssi)
{
    if (ConnectivityMgrImpl().GetWiFiIfName() == nullptr)
    {
        return CHIP_ERROR_READ_FAILED;
    }

    return ConnectivityUtils::GetWiFiRssi(ConnectivityMgrImpl().GetWiFiIfName(), rssi);
}

CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiBeaconLostCount(uint32_t & beaconLostCount)
{
    uint32_t count;

    if (ConnectivityMgrImpl().GetWiFiIfName() == nullptr)
    {
        return CHIP_ERROR_READ_FAILED;
    }

    ReturnErrorOnFailure(ConnectivityUtils::GetWiFiBeaconLostCount(ConnectivityMgrImpl().GetWiFiIfName(), count));
    VerifyOrReturnError(count >= mBeaconLostCount, CHIP_ERROR_INVALID_INTEGER_VALUE);
    beaconLostCount = count - mBeaconLostCount;

    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiCurrentMaxRate(uint64_t & currentMaxRate)
{
    if (ConnectivityMgrImpl().GetWiFiIfName() == nullptr)
    {
        return CHIP_ERROR_READ_FAILED;
    }

    return ConnectivityUtils::GetWiFiCurrentMaxRate(ConnectivityMgrImpl().GetWiFiIfName(), currentMaxRate);
}

CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiPacketMulticastRxCount(uint32_t & packetMulticastRxCount)
{
    int ret;
    NCP_CMD_PKT_STATS stats;

    ret = wlan_ncp_get_pkt_stats(&stats);
    if (ret != WM_SUCCESS)
    {
        ChipLogError(DeviceLayer, "wlan_ncp_get_pkt_stats failed ");
    }
    packetMulticastRxCount = stats.mcast_rx_frame;

    ChipLogProgress(DeviceLayer, "GetWiFiPacketMulticastRxCount: %lu ", packetMulticastRxCount);
    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiPacketMulticastTxCount(uint32_t & packetMulticastTxCount)
{
    int ret;
    NCP_CMD_PKT_STATS stats;

    ret = wlan_ncp_get_pkt_stats(&stats);
    if (ret != WM_SUCCESS)
    {
        ChipLogError(DeviceLayer, "wlan_ncp_get_pkt_stats failed ");
    }

    packetMulticastTxCount = stats.mcast_tx_frame;

    ChipLogProgress(DeviceLayer, "GetWiFiPacketMulticastTxCount: %lu ", packetMulticastTxCount);
    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiPacketUnicastRxCount(uint32_t & packetUnicastRxCount)
{
    int ret;
    NCP_CMD_PKT_STATS stats;

    ret = wlan_ncp_get_pkt_stats(&stats);
    if (ret != WM_SUCCESS)
    {
        ChipLogError(DeviceLayer, "wlan_ncp_get_pkt_stats failed ");
    }

    packetUnicastRxCount = stats.rx_unicast_cnt;
    ChipLogProgress(DeviceLayer, "GetWiFiPacketUnicastRxCount: %lu (ToDo)", packetUnicastRxCount);
    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiPacketUnicastTxCount(uint32_t & packetUnicastTxCount)
{
    int ret;
    NCP_CMD_PKT_STATS stats;

    ret = wlan_ncp_get_pkt_stats(&stats);
    if (ret != WM_SUCCESS)
    {
        ChipLogError(DeviceLayer, "wlan_ncp_get_pkt_stats failed ");
    }

    /* fix me: wifi drv will update the struct later */
    packetUnicastTxCount = stats.tx_frame - stats.mcast_tx_frame;

    ChipLogProgress(DeviceLayer, "GetWiFiPacketUnicastTxCount: %lu", packetUnicastTxCount);
    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiOverrunCount(uint64_t & overrunCount)
{
    int ret;
    NCP_CMD_PKT_STATS stats;

    ret = wlan_ncp_get_pkt_stats(&stats);
    if (ret != WM_SUCCESS)
    {
        ChipLogError(DeviceLayer, "wlan_ncp_get_pkt_stats failed ");
    }

    overrunCount = (stats.tx_overrun_cnt + stats.rx_overrun_cnt) - mOverrunCount;

    ChipLogProgress(DeviceLayer, "GetWiFiOverrunCount: %lu", overrunCount);
    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::ResetWiFiNetworkDiagnosticsCounts()
{
    return CHIP_NO_ERROR;
}
#endif // CHIP_DEVICE_CONFIG_ENABLE_WIFI

#if CHIP_DEVICE_CONFIG_ENABLE_WPA
CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiVersion(app::Clusters::WiFiNetworkDiagnostics::WiFiVersionEnum & wiFiVersion)
{
    return ConnectivityMgrImpl().GetWiFiVersion(wiFiVersion);
}

CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiBssId(MutableByteSpan & value)
{
    return ConnectivityMgrImpl().GetWiFiBssId(value);
}

CHIP_ERROR DiagnosticDataProviderImpl::GetWiFiSecurityType(app::Clusters::WiFiNetworkDiagnostics::SecurityTypeEnum & securityType)
{
    return ConnectivityMgrImpl().GetWiFiSecurityType(securityType);
}
#endif // CHIP_DEVICE_CONFIG_ENABLE_WPA

DiagnosticDataProvider & GetDiagnosticDataProviderImpl()
{
    return DiagnosticDataProviderImpl::GetDefaultInstance();
}

} // namespace DeviceLayer
} // namespace chip
