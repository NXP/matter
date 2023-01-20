/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
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
#include <lib/shell/Engine.h>
#include <lib/core/CHIPCore.h>
#include <lib/support/Base64.h>
#include <lib/support/CHIPArgParser.hpp>
#include <lib/support/CodeUtils.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/logging/CHIPLogging.h>

#include <app-common/zap-generated/attribute-id.h>
#include <app-common/zap-generated/cluster-id.h>
//#include <app-common/zap-generated/ids/Clusters.h>
#include <app/server/Dnssd.h>
#include <app/server/Server.h>
#include <app/util/af-types.h>
#include <app/util/attribute-storage.h>
#include <app/util/attribute-table.h>
#include <app/server/OnboardingCodesUtil.h>
//#include <app/clusters/bindings/BindingManager.h>
#include <app/InteractionModelEngine.h>

#include <platform/CHIPDeviceLayer.h>
#include <setup_payload/SetupPayload.h>
#include <setup_payload/QRCodeSetupPayloadGenerator.h>
#include <ChipShellCollection.h>
#include <platform/nxp/mw320/ConnectivityUtils.h>

#if (defined(CONFIG_CHIP_MW320_REAL_FACTORY_DATA) && (CONFIG_CHIP_MW320_REAL_FACTORY_DATA == 1))
#include "FactoryDataProvider.h"
#else
#include <credentials/DeviceAttestationCredsProvider.h>
#include <credentials/examples/DeviceAttestationCredsExample.h>
#endif // if CONFIG_CHIP_MW320_REAL_FACTORY_DATA

#include <app/clusters/ota-requestor/BDXDownloader.h>
#include <app/clusters/ota-requestor/DefaultOTARequestor.h>
#include <app/clusters/ota-requestor/DefaultOTARequestorDriver.h>
#include <app/clusters/ota-requestor/DefaultOTARequestorStorage.h>
//#include <app/clusters/ota-requestor/DefaultOTARequestorUserConsent.h>
#include "platform/nxp/mw320/OTAImageProcessorImpl.h"
//#include "app/clusters/ota-requestor/OTARequestorDriver.h"

// for ota module test
#include "mw320_ota.h"

#include "binding-handler.h"
#include "AppTask.h"
#include "CHIPProjectConfig.h"

extern "C" {
#include "dhcp-server.h"
#include "network_flash_storage.h"
#include "wlan.h"
#include "wm_net.h"
}

using namespace chip;
using namespace chip::Credentials;
using namespace ::chip::app;
using namespace chip::Shell;
using namespace chip::DeviceLayer;

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SSID_FNAME "ssid_fname"
#define PSK_FNAME "psk_fname"

/*******************************************************************************
 * Variables
 ******************************************************************************/
static struct wlan_network sta_network;
static struct wlan_network uap_network;

const int TASK_MAIN_PRIO         = OS_PRIO_3;
const int TASK_MAIN_STACK_SIZE   = 800;
portSTACK_TYPE * task_main_stack = NULL;
TaskHandle_t task_main_task_handler;
TaskHandle_t sShellTaskHandle;

//uint8_t * __FACTORY_DATA_START;
//uint32_t __FACTORY_DATA_SIZE;

typedef enum
{
    chip_srv_all,
    dns_srv,
    srv_type_max
} srv_type_t;

static bool is_connected = false;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void load_network(char * ssid, char * pwd);
static int wlan_event_callback(enum wlan_event_reason reason, void * data);
static void run_chip_srv(System::Layer * aSystemLayer, void * aAppState);
static void run_dnssrv(System::Layer * aSystemLayer, void * aAppState);
static void run_update_chipsrv(srv_type_t srv_type);

using chip::BDXDownloader;
using chip::DefaultOTARequestor;
using chip::OTADownloader;
using chip::OTAImageProcessorImpl;
using chip::OTAImageProgress;

DefaultOTARequestor gRequestorCore;
DefaultOTARequestorStorage gRequestorStorage;
chip::DeviceLayer::DefaultOTARequestorDriver gRequestorUser;
BDXDownloader gDownloader;
OTAImageProcessorImpl gImageProcessor;
// chip::ota::DefaultOTARequestorUserConsent gUserConsentProvider;
// static chip::ota::UserConsentState gUserConsentState = chip::ota::UserConsentState::kGranted;
static void InitOTARequestor(void);
const char * mw320_get_verstr(void);
void save_network(char * ssid, char * pwd);

static void InitOTARequestor(void)
{
    // Initialize and interconnect the Requestor and Image Processor objects -- START
    SetRequestorInstance(&gRequestorCore);

    gRequestorStorage.Init(chip::Server::GetInstance().GetPersistentStorage());

    // Set server instance used for session establishment
    gRequestorCore.Init(chip::Server::GetInstance(), gRequestorStorage, gRequestorUser, gDownloader);

    // WARNING: this is probably not realistic to know such details of the image or to even have an OTADownloader instantiated at
    // the beginning of program execution. We're using hardcoded values here for now since this is a reference application.
    // TODO: instatiate and initialize these values when QueryImageResponse tells us an image is available
    // TODO: add API for OTARequestor to pass QueryImageResponse info to the application to use for OTADownloader init
    // OTAImageProcessor ipParams;
    // ipParams.imageFile = CharSpan("dnld_img.txt");
    // gImageProcessor.SetOTAImageProcessorParams(ipParams);
    gImageProcessor.SetOTADownloader(&gDownloader);

    // Connect the Downloader and Image Processor objects
    gDownloader.SetImageProcessorDelegate(&gImageProcessor);
    gRequestorUser.Init(&gRequestorCore, &gImageProcessor);
    /*
        if (gUserConsentState != chip::ota::UserConsentState::kUnknown)
        {
            gUserConsentProvider.SetUserConsentState(gUserConsentState);
            gRequestorUser.SetUserConsentDelegate(&gUserConsentProvider);
        }
    */
    // Initialize and interconnect the Requestor and Image Processor objects -- END
}

/*
static void saveProfile(int argc, char **argv);
static void loadProfile(int argc, char **argv);
static void resetProfile(int argc, char **argv);

static void wlanIeeePowerSave(int argc, char **argv);
static void wlanDeepSleep(int argc, char **argv);
static void mcuPowerMode(int argc, char **argv);


static struct cli_command saveload[] = {
    {"save-profile", "<profile_name>", saveProfile},
    {"load-profile", NULL, loadProfile},
    {"reset-profile", NULL, resetProfile},
};

static struct cli_command wlanPower[] = {
    {"wlan-ieee-power-save", "<on/off> <wakeup condition>", wlanIeeePowerSave},
    {"wlan-deepsleep", "<on/off>", wlanDeepSleep},
};

static struct cli_command mcuPower[] = {
    {"mcu-power-mode", "<pm0/pm1/pm2/pm4> [<pm2_io_exclude_mask>]", mcuPowerMode},
};
*/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void load_network(char * ssid, char * pwd)
{
    int ret;
    unsigned char ssid_buf[IEEEtypes_SSID_SIZE + 1];
    unsigned char psk_buf[WLAN_PSK_MAX_LENGTH];
    uint32_t len;

    len = IEEEtypes_SSID_SIZE + 1;
    ret = get_saved_wifi_network((char *) SSID_FNAME, ssid_buf, &len);
    if (ret != WM_SUCCESS)
    {
        PRINTF("Error: Read saved SSID\r\n");
        strcpy(ssid, "");
    }
    else
    {
        PRINTF("saved_ssid: [%s]\r\n", ssid_buf);
        strcpy(ssid, (const char *) ssid_buf);
    }

    len = WLAN_PSK_MAX_LENGTH;
    ret = get_saved_wifi_network((char *) PSK_FNAME, psk_buf, &len);
    if (ret != WM_SUCCESS)
    {
        PRINTF("Error: Read saved PSK\r\n");
        strcpy(pwd, "");
    }
    else
    {
        PRINTF("saved_psk: [%s]\r\n", psk_buf);
        strcpy(pwd, (const char *) psk_buf);
    }
}

/*
static void saveProfile(int argc, char **argv)
{
    int ret;
    struct wlan_network network;

    if (argc < 2)
    {
        PRINTF("Usage: %s <profile_name>\r\n", argv[0]);
        PRINTF("Error: specify network to save\r\n");
        return;
    }

    ret = wlan_get_network_byname(argv[1], &network);
    if (ret != WM_SUCCESS)
    {
        PRINTF("Error: network not found\r\n");
    }
    else
    {
        ret = save_wifi_network((char *)CONNECTION_INFO_FILENAME, (uint8_t *)&network, sizeof(network));
        if (ret != WM_SUCCESS)
        {
            PRINTF("Error: write network to flash failed\r\n");
        }
    }
}

static void loadProfile(int argc, char **argv)
{
    int ret;
    struct wlan_network network;
    uint32_t len = sizeof(network);

    ret = get_saved_wifi_network((char *)CONNECTION_INFO_FILENAME, (uint8_t *)&network, &len);
    if (ret != WM_SUCCESS || len != sizeof(network))
    {
        PRINTF("Error: No network saved\r\n");
    }
    else
    {
        ret = wlan_add_network(&network);
        if (ret != WM_SUCCESS)
        {
            PRINTF("Error: network data corrupted or network already added\r\n");
        }
    }
}

static void resetProfile(int argc, char **argv)
{
    int ret;

    ret = reset_saved_wifi_network((char *)CONNECTION_INFO_FILENAME);
    if (ret != WM_SUCCESS)
    {
        PRINTF("Error: Reset profile failed\r\n");
    }
}

static void wlanIeeePowerSave(int argc, char **argv)
{
    bool on  = false;
    bool off = false;
    uint32_t cond;
    int ret;

    if (argc >= 2)
    {
        on  = (strcmp(argv[1], "on") == 0);
        off = (strcmp(argv[1], "off") == 0);
    }
    if ((argc < 2) || (!on && !off) || (on && argc < 3))
    {
        PRINTF("Usage: %s <on/off> [<wakeup condition>]\r\n", argv[0]);
        PRINTF("       wakeup condictions needed by \"on\" command:\r\n");
        PRINTF("       bit0=1: broadcast data\r\n");
        PRINTF("       bit1=1: unicast data\r\n");
        PRINTF("       bit2=1: mac events\r\n");
        PRINTF("       bit3=1: multicast data\r\n");
        PRINTF("       bit4=1: arp broadcast data\r\n");
        PRINTF("       bit6=1: management frame\r\n");
        return;
    }

    if (on)
    {
        cond = strtoul(argv[2], NULL, 0);
        ret  = wlan_ieeeps_on(cond);
    }
    else
    {
        ret = wlan_ieeeps_off();
    }

    if (ret != WM_SUCCESS)
    {
        PRINTF("Cannot request IEEE power save mode change!\r\n");
    }
    else
    {
        PRINTF("IEEE power save mode change requested!\r\n");
    }
}

static void wlanDeepSleep(int argc, char **argv)
{
    bool on;
    int ret;

    if ((argc < 2) || ((strcmp(argv[1], "on") != 0) && (strcmp(argv[1], "off") != 0)))
    {
        PRINTF("Usage: %s <on/off>\r\n", argv[0]);
        PRINTF("Error: specify deep sleep on or off.\r\n");
        return;
    }

    on = (strcmp(argv[1], "on") == 0);
    if (on)
    {
        ret = wlan_deepsleepps_on();
    }
    else
    {
        ret = wlan_deepsleepps_off();
    }

    if (ret != WM_SUCCESS)
    {
        PRINTF("Cannot request deep sleep mode change!\r\n");
    }
    else
    {
        PRINTF("Deep sleep mode change requested!\r\n");
    }
}


static void mcuPowerMode(int argc, char **argv)
{
    uint32_t excludeIo = 0U;

    if ((argc < 2) || (strlen(argv[1]) != 3) || (argv[1][0] != 'p') || (argv[1][1] != 'm') || (argv[1][2] < '0') ||
        (argv[1][2] > '4') || (argv[1][2] == '3'))
    {
        PRINTF("Usage: %s <pm0/pm1/pm2/pm4> [<pm2_io_exclude_mask>]\r\n", argv[0]);
        PRINTF("       pm2_io_exclude_mask: bitmask of io domains to keep on in PM2.\r\n");
        PRINTF("                            e.g. 0x5 means VDDIO0 and VDDIO2 will not be powered off in PM2\r\n");
        PRINTF("Error: specify power mode to enter.\r\n");
        return;
    }

    if (argv[1][2] - '0' == 2U)
    {
        if (argc < 3)
        {
            PRINTF("Error: PM2 need 3rd parameter.\r\n");
            return;
        }
        else
        {
            excludeIo = strtoul(argv[2], NULL, 0);
        }
    }

    LPM_SetPowerMode(argv[1][2] - '0', excludeIo);
}
*/

/* Callback Function passed to WLAN Connection Manager. The callback function
 * gets called when there are WLAN Events that need to be handled by the
 * application.
 */
static int wlan_event_callback (enum wlan_event_reason reason, void * data)
{
    int ret;
    struct wlan_ip_config addr;
    char ip[16];
    static int auth_fail = 0;

    //    PRINTF("[%s] WLAN: received event %d\r\n", __FUNCTION__, reason);
    switch (reason)
    {
    case WLAN_REASON_INITIALIZED:
        // PRINTF("app_cb: WLAN initialized\r\n");
#ifdef MCUXPRESSO_WIFI_CLI
        ret = wlan_basic_cli_init();
        if (ret != WM_SUCCESS)
        {
            PRINTF("Failed to initialize BASIC WLAN CLIs\r\n");
            return 0;
        }

        ret = wlan_cli_init();
        if (ret != WM_SUCCESS)
        {
            PRINTF("Failed to initialize WLAN CLIs\r\n");
            return 0;
        }
        PRINTF("WLAN CLIs are initialized\r\n");

        ret = ping_cli_init();
        if (ret != WM_SUCCESS)
        {
            PRINTF("Failed to initialize PING CLI\r\n");
            return 0;
        }

        ret = iperf_cli_init();
        if (ret != WM_SUCCESS)
        {
            PRINTF("Failed to initialize IPERF CLI\r\n");
            return 0;
        }
#endif
        ret = dhcpd_cli_init();
        if (ret != WM_SUCCESS)
        {
            // PRINTF("Failed to initialize DHCP Server CLI\r\n");
            return 0;
        }
#ifdef MCUXPRESSO_WIFI_CLI
        if (cli_register_commands(saveload, sizeof(saveload) / sizeof(struct cli_command)))
        {
            return -WM_FAIL;
        }

        if (cli_register_commands(wlanPower, sizeof(wlanPower) / sizeof(struct cli_command)))
        {
            return -WM_FAIL;
        }

        if (cli_register_commands(mcuPower, sizeof(mcuPower) / sizeof(struct cli_command)))
        {
            return -WM_FAIL;
        }

        PRINTF("CLIs Available:\r\n");
        if (Matter_Selection == MCUXPRESSO_WIFI_CLI)
            help_command(0, NULL);
#endif
        break;
    case WLAN_REASON_INITIALIZATION_FAILED:
        // PRINTF("app_cb: WLAN: initialization failed\r\n");
        break;
    case WLAN_REASON_SUCCESS:
        // PRINTF("app_cb: WLAN: connected to network\r\n");
        ret = wlan_get_address(&addr);
        if (ret != WM_SUCCESS)
        {
            // PRINTF("failed to get IP address\r\n");
            return 0;
        }

        net_inet_ntoa(addr.ipv4.address, ip);

        ret = wlan_get_current_network(&sta_network);
        if (ret != WM_SUCCESS)
        {
            // PRINTF("Failed to get External AP network\r\n");
            return 0;
        }

        PRINTF("Connected to following BSS:\r\n");
        PRINTF("SSID = [%s], IP = [%s]\r\n", sta_network.ssid, ip);
        save_network(sta_network.ssid, sta_network.security.psk);

#ifdef CONFIG_IPV6
        {
            int i;
            (void) PRINTF("\r\n\tIPv6 Addresses\r\n");
            for (i = 0; i < MAX_IPV6_ADDRESSES; i++)
            {
                if (sta_network.ip.ipv6[i].addr_state != IP6_ADDR_INVALID)
                {
                    (void) PRINTF("\t%-13s:\t%s (%s)\r\n", ipv6_addr_type_to_desc(&(sta_network.ip.ipv6[i])),
                                  inet6_ntoa(sta_network.ip.ipv6[i].address),
                                  ipv6_addr_state_to_desc(sta_network.ip.ipv6[i].addr_state));
                }
            }
            (void) PRINTF("\r\n");
        }
#endif
        auth_fail    = 0;
        is_connected = true;
        run_update_chipsrv(dns_srv);

        if (is_uap_started())
        {
            wlan_get_current_uap_network(&uap_network);
            ret = wlan_stop_network(uap_network.name);
            /*
			if (ret != WM_SUCCESS)
				PRINTF("Error: unable to stop network\r\n");
			else
					PRINTF("stop uAP, SSID = [%s]\r\n", uap_network.ssid);
            */
        }
        break;
    case WLAN_REASON_CONNECT_FAILED:
        //            PRINTF("app_cb: WLAN: connect failed\r\n");
        break;
    case WLAN_REASON_NETWORK_NOT_FOUND:
        //            PRINTF("app_cb: WLAN: network not found\r\n");
        break;
    case WLAN_REASON_NETWORK_AUTH_FAILED:
        //            PRINTF("app_cb: WLAN: network authentication failed\r\n");
        auth_fail++;
        if (auth_fail >= 3)
        {
            //                PRINTF("Authentication Failed. Disconnecting ... \r\n");
            wlan_disconnect();
            auth_fail = 0;
        }
        break;
    case WLAN_REASON_ADDRESS_SUCCESS:
        //            PRINTF("network mgr: DHCP new lease\r\n");
        break;
    case WLAN_REASON_ADDRESS_FAILED:
        //            PRINTF("app_cb: failed to obtain an IP address\r\n");
        break;
    case WLAN_REASON_USER_DISCONNECT:
        //            PRINTF("app_cb: disconnected\r\n");
        auth_fail = 0;
        break;
    case WLAN_REASON_LINK_LOST:
        is_connected = false;
        run_update_chipsrv(dns_srv);
        //            PRINTF("app_cb: WLAN: link lost\r\n");
        break;
    case WLAN_REASON_CHAN_SWITCH:
        //            PRINTF("app_cb: WLAN: channel switch\r\n");
        break;
    case WLAN_REASON_UAP_SUCCESS:
        //            PRINTF("app_cb: WLAN: UAP Started\r\n");
        ret = wlan_get_current_uap_network(&uap_network);

        if (ret != WM_SUCCESS)
        {
            PRINTF("Failed to get Soft AP network\r\n");
            return 0;
        }

        //            PRINTF("Soft AP \"%s\" started successfully\r\n", uap_network.ssid);
        if (dhcp_server_start(net_get_uap_handle()))
            PRINTF("Error in starting dhcp server\r\n");
        //            PRINTF("DHCP Server started successfully\r\n");
        break;
    case WLAN_REASON_UAP_CLIENT_ASSOC:
        PRINTF("app_cb: WLAN: UAP a Client Associated\r\n");
        //            PRINTF("Client => ");
        //            print_mac((const char *)data);
        //            PRINTF("Associated with Soft AP\r\n");
        break;
    case WLAN_REASON_UAP_CLIENT_DISSOC:
        //            PRINTF("app_cb: WLAN: UAP a Client Dissociated\r\n");
        //            PRINTF("Client => ");
        //            print_mac((const char *)data);
        //            PRINTF("Dis-Associated from Soft AP\r\n");
        break;
    case WLAN_REASON_UAP_STOPPED:
        //            PRINTF("app_cb: WLAN: UAP Stopped\r\n");
        //            PRINTF("Soft AP \"%s\" stopped successfully\r\n", uap_network.ssid);
        dhcp_server_stop();
        //            PRINTF("DHCP Server stopped successfully\r\n");
        break;
    case WLAN_REASON_PS_ENTER:
        //            PRINTF("app_cb: WLAN: PS_ENTER\r\n");
        break;
    case WLAN_REASON_PS_EXIT:
        //            PRINTF("app_cb: WLAN: PS EXIT\r\n");
        break;
    default:
        PRINTF("app_cb: WLAN: Unknown Event: %d\r\n", reason);
    }
    return 0;
}

#if 0
char profile[8] = "mw320";
char ssid[32] = "matter_mw320";
char psk[64] = "12345678";
char network_ip[15] = "192.168.2.1";
char network_netmask[15] = "255.255.255.0";
const uint8_t kOptionalDefaultStringTag1       = 1;
const uint8_t kOptionalDefaultStringTag2       = 2;
const uint8_t kOptionalDefaultStringTag3       = 3;

std::string createSetupPayload()
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    std::string result;
    std::string kOptionalDefaultStringValue1 = "IP:";
    std::string kOptionalDefaultStringValue2 = "SSID:";
    std::string kOptionalDefaultStringValue3 = "Key:";
    uint16_t discriminator;

    kOptionalDefaultStringValue1.append( network_ip, sizeof(network_ip) );
    kOptionalDefaultStringValue2.append( ssid, sizeof(ssid) );
    kOptionalDefaultStringValue3.append( psk, sizeof(psk) );
    err = ConfigurationMgr().GetSetupDiscriminator(discriminator);
    if (err != CHIP_NO_ERROR)
    {
        PRINTF("[%s]: Couldn't get discriminator: %s\r\n", __FUNCTION__, ErrorStr(err));
        return result;
    }

    uint32_t setupPINCode;
    err = ConfigurationMgr().GetSetupPinCode(setupPINCode);
    if (err != CHIP_NO_ERROR)
    {
        PRINTF("[%s]: Couldn't get setupPINCode: %s\r\n", __FUNCTION__, ErrorStr(err));
        return result;
    }

    uint16_t vendorId;
    err = ConfigurationMgr().GetVendorId(vendorId);
    if (err != CHIP_NO_ERROR)
    {
        PRINTF("[%s]: Couldn't get vendorId: %s\r\n", __FUNCTION__, ErrorStr(err));
        return result;
    }

    uint16_t productId;
    err = ConfigurationMgr().GetProductId(productId);
    if (err != CHIP_NO_ERROR)
    {
        PRINTF("[%s]: Couldn't get productId: %s\r\n", __FUNCTION__, ErrorStr(err));
        return result;
    }
    SetupPayload payload;
    payload.version               = 0;
    payload.discriminator         = discriminator;
    payload.setUpPINCode          = setupPINCode;
    payload.rendezvousInformation.SetValue(chip::RendezvousInformationFlag::kBLE);
    payload.vendorID              = vendorId;
    payload.productID             = productId;

    err = payload.addOptionalVendorData(kOptionalDefaultStringTag1, kOptionalDefaultStringValue1);
    if (err != CHIP_NO_ERROR)
    {
        PRINTF("[%s]: Couldn't add payload Vnedor string %d \r\n", __FUNCTION__, kOptionalDefaultStringTag1);
    }
    err = payload.addOptionalVendorData(kOptionalDefaultStringTag2, kOptionalDefaultStringValue2);
    if (err != CHIP_NO_ERROR)
    {
        PRINTF("[%s]: Couldn't add payload Vnedor string %d \r\n", __FUNCTION__, kOptionalDefaultStringTag2);
    }
    err = payload.addOptionalVendorData(kOptionalDefaultStringTag3, kOptionalDefaultStringValue3);
    if (err != CHIP_NO_ERROR)
    {
        PRINTF("[%s]: Couldn't add payload Vnedor string %d \r\n", __FUNCTION__, kOptionalDefaultStringTag3);
    }

    QRCodeSetupPayloadGenerator generator(payload);
    size_t tlvDataLen = sizeof(kOptionalDefaultStringValue1)+sizeof(kOptionalDefaultStringValue2)+sizeof(kOptionalDefaultStringValue3);
    uint8_t tlvDataStart[tlvDataLen];
    err = generator.payloadBase38Representation(result, tlvDataStart, tlvDataLen);

    if (err != CHIP_NO_ERROR)
    {
        PRINTF("[%s]: Couldn't get payload string %d \r\n", __FUNCTION__, err);
    }
    return result;
}
#endif // 0

static void run_chip_srv(System::Layer * aSystemLayer, void * aAppState)
{
    // Init ZCL Data Model and CHIP App Server
    {
        // Initialize device attestation config
#if (defined(CONFIG_CHIP_MW320_REAL_FACTORY_DATA) && (CONFIG_CHIP_MW320_REAL_FACTORY_DATA == 1))
        FactoryDataProvider::GetDefaultInstance().Init();
#if (CHIP_DEVICE_CONFIG_ENABLE_DEVICE_INSTANCE_INFO_PROVIDER == 1)
        SetDeviceInstanceInfoProvider(&FactoryDataProvider::GetDefaultInstance());
#endif // USE_LOCAL_DEVICEINSTANCEINFOPROVIDER
        SetDeviceAttestationCredentialsProvider(&FactoryDataProvider::GetDefaultInstance());
        SetCommissionableDataProvider(&FactoryDataProvider::GetDefaultInstance());
#else
        SetDeviceAttestationCredentialsProvider(Examples::GetExampleDACProvider());
#endif // CONFIG_CHIP_MW320_REAL_FACTORY_DATA
    }
    {
        //    chip::Server::GetInstance().Init();
        // uint16_t securePort   = CHIP_PORT;
        // uint16_t unsecurePort = CHIP_UDC_PORT;

        // PRINTF("==> call chip::Server() \r\n");
        // chip::Server::GetInstance().Init(nullptr, securePort, unsecurePort);

        static chip::CommonCaseDeviceServerInitParams initParams;
        (void) initParams.InitializeStaticResourcesBeforeServerInit();
        chip::Server::GetInstance().Init(initParams);
        PRINTF("Done to call chip::Server() \r\n");
    }
    // ota ++
    {
        InitOTARequestor();
#if (MW320_OTA_TEST == 1)
        // for ota module test
        mw320_fw_update_test();
#endif // MW320_OTA_TEST
    }
    // ota --
    // binding ++
    //InitBindingHandlers();
    // binding --

    return;
}

static void run_dnssrv(System::Layer * aSystemLayer, void * aAppState)
{
    chip::app::DnssdServer::Instance().StartServer();
    if (is_connected == true)
    {
        led_on_off(led_amber, true);
    }
    else
    {
        led_on_off(led_amber, false);
    }
    return;
}

#define RUN_CHIPSRV_DELAY 1
static void run_update_chipsrv(srv_type_t srv_type)
{
    switch (srv_type)
    {
    case chip_srv_all:
        DeviceLayer::SystemLayer().StartTimer(System::Clock::Seconds16(RUN_CHIPSRV_DELAY), run_chip_srv, nullptr);
        break;
    case dns_srv:
        DeviceLayer::SystemLayer().StartTimer(System::Clock::Seconds16(RUN_CHIPSRV_DELAY), run_dnssrv, nullptr);
        break;
    default:
        return;
    }
    return;
}

static void task_test_main(void * param)
{
    while (1)
    {
        /* wait for interface up */
        os_thread_sleep(os_msec_to_ticks(500));
        /*PRINTF("[%s]: looping\r\n", __FUNCTION__);*/
        if (need2sync_sw_attr == true)
        {
            static bool is_on = false;
            uint16_t value    = g_ButtonPress & 0x1;
            is_on             = !is_on;
            value             = (uint16_t) is_on;
            // sync-up the switch attribute:
            PRINTF("--> update ZCL_CURRENT_POSITION_ATTRIBUTE_ID [%d] \r\n", value);
            emAfWriteAttribute(1, ZCL_SWITCH_CLUSTER_ID, ZCL_CURRENT_POSITION_ATTRIBUTE_ID, (uint8_t *) &value, sizeof(value), true,
                               false);
#ifdef SUPPORT_MANUAL_CTRL
            // sync-up the Light attribute (for test event, OO.M.ManuallyControlled)
            PRINTF("--> update [ZCL_ON_OFF_CLUSTER_ID]: ZCL_ON_OFF_ATTRIBUTE_ID [%d] \r\n", value);
            emAfWriteAttribute(1, ZCL_ON_OFF_CLUSTER_ID, ZCL_ON_OFF_ATTRIBUTE_ID, (uint8_t *) &value, sizeof(value), true, false);
#endif // SUPPORT_MANUAL_CTRL
            // Trigger to send on/off/toggle command to the bound devices
            //chip::BindingManager::GetInstance().NotifyBoundClusterChanged(1, chip::app::Clusters::OnOff::Id, nullptr);

            need2sync_sw_attr = false;
        }
        // =============================
        // Call sw2_handle to clear click_count if needed
        sw2_handle(false);
        // =============================
    }
    return;
}

static void ShellCLIMain(void * pvParameter)
{
    const int rc = streamer_init(streamer_get());
    if (rc != 0)
    {
        ChipLogError(Shell, "Streamer initialization failed: %d", rc);
        return;
    }

    PRINTF("version: [%s] \r\n", mw320_get_verstr());

    // Initialize the SDK components
    init_mw320_sdk(wlan_event_callback);

    ChipLogDetail(Shell, "Initializing CHIP shell commands: %d", rc);

    chip::Platform::MemoryInit();
    chip::DeviceLayer::PlatformMgr().InitChipStack();
    ConfigurationMgr().LogDeviceConfig();
    PrintOnboardingCodes(chip::RendezvousInformationFlag::kOnNetwork);
    chip::DeviceLayer::PlatformMgr().StartEventLoopTask();
#if CHIP_DEVICE_CONFIG_ENABLE_WPA
    chip::DeviceLayer::ConnectivityManagerImpl().StartWiFiManagement();
#endif

    cmd_misc_init();
    // cmd_otcli_init();
    ChipLogDetail(Shell, "Run CHIP shell Task: %d", rc);

    //    std::string qrCodeText = createSetupPayload();
    //    PRINTF("SetupQRCode: [%s]\r\n", qrCodeText.c_str());
    {
        char def_ssid[IEEEtypes_SSID_SIZE + 1];
        char def_psk[WLAN_PSK_MAX_LENGTH];
        load_network(def_ssid, def_psk);

        if ((strlen(def_ssid) <= 0) || (strlen(def_psk) <= 0))
        {
            // No saved connected_ap_info => Using the default ssid/password
            strcpy(def_ssid, "nxp_matter");
            strcpy(def_psk, "nxp12345");
        }
        PRINTF("Connecting to [%s, %s] \r\n", def_ssid, def_psk);
        //ConnectivityMgrImpl().ProvisionWiFiNetwork(def_ssid, def_psk);
	chip::DeviceLayer::Internal::ConnectivityUtils::ConnectWiFiNetwork(def_ssid, def_psk);
    }

    // Run CHIP servers
    run_update_chipsrv(chip_srv_all);

    Engine::Root().RunMainLoop();
}

static int StartShellTask(void)
{
    int ret = 0;

    // Start Shell task.
    if (xTaskCreate(ShellCLIMain, "SHELL", TASK_MAIN_STACK_SIZE, NULL, TASK_MAIN_PRIO, &sShellTaskHandle) != pdPASS)
    {
        ret = -1;
    }
    if (xTaskCreate(task_test_main, "testmain", TASK_MAIN_STACK_SIZE, task_main_stack, TASK_MAIN_PRIO,
                    &task_main_task_handler) != pdPASS)
    {
        PRINTF("Failed to crete task_test_main() \r\n");
        ret = -1;
    }

    return ret;
}

const char * mw320_get_verstr(void)
{
    return CHIP_DEVICE_CONFIG_DEVICE_SOFTWARE_VERSION_STRING;
}

void save_network(char * ssid, char * pwd)
{
    int ret;

    ret = save_wifi_network((char *) SSID_FNAME, (uint8_t *) ssid, strlen(ssid) + 1);
    if (ret != WM_SUCCESS)
    {
        PRINTF("Error: write ssid to flash failed\r\n");
    }

    ret = save_wifi_network((char *) PSK_FNAME, (uint8_t *) pwd, strlen(pwd) + 1);
    if (ret != WM_SUCCESS)
    {
        PRINTF("Error: write psk to flash failed\r\n");
    }

    return;
}


int main(void)
{
	// Init mw320 board
	board_init();

	// Start the shell
    StartShellTask();

    /* Start FreeRTOS */
    vTaskStartScheduler();

    return 0;
}
