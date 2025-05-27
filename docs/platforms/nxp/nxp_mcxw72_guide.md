# Matter NXP MCXW72 Applications Guide

-   [Introduction](#introduction)
-   [Building](#building)
-   [Manufacturing Data](#manufacturing-data)
-   [Flashing and debugging](#flashing-and-debugging)
-   [Testing the example](#testing-the-example)
-   [OTA Software Update](#ota-software-update)

<hr>

<a name="introduction"></a>

## Introduction

The Matter MCXW72 example applications provide a working demonstration of the
MCXW72 board integration, built using the Project CHIP codebase and the NXP MCUX
SDK.

### Supported configurations

The examples support:

-   Matter over Openthread

### Supported build systems

MCXW72 platform supports two different build systems to generate the application
:

-   `GN`
-   `CMake`

<a name="building"></a>

## Building

Make sure to follow shared build instructions from
[CHIP NXP Examples Guide for FreeRTOS platforms](./nxp_examples_freertos_platforms.md#set-up-the-build-environment)
to set-up your environment.

> In the following steps, the "lighting-app" is used as an example.

### CMake Build System

The example supports configuration and build with CMake build system. You can
find more information in
[CMake Build System](./nxp_examples_freertos_platforms.md#cmake-build-system)
section which explains how to further configure your application build.

In the `west build` command, the `board` option can be replaced with
`frdmmcxw72` if using `NXP FRDM-MCXW72` board, or `mcxw72evk` if using
`NXP MCXW72-EVK` board. The `core_id` should be set to `cm33_core0`. The Kconfig
`-DCONFIG_MCUX_COMPONENT_middleware.freertos-kernel.config=n` must be set in the
build command for the mcxw72 platform.

Example of build command to build the Lighting app with Matter-over-Thread (FTD
device type) configuration on MCXW72 platform :

```
user@ubuntu:~/Desktop/git/connectedhomeip$ west build -d <build_dir> -b frdmmcxw72 examples/lighting-app/nxp -Dcore_id=cm33_core0 -DCONF_FILE_NAME=prj_thread_ftd.conf -DCONFIG_MCUX_COMPONENT_middleware.freertos-kernel.config=n
```

Note that the MCXW72 example supports various configurations that can be
provided to the `CONF_FILE_NAME` variable, you can refer to the
[table of available project configuration files and platform compatibility](./nxp_examples_freertos_platforms.md#available-project-configuration-files-and-platform-compatibility)
to check all the supported configurations.

> Note : BLE and Matter-CLI are enabled by default in Matter applications built
> with CMake. To disable them, you can refer to the
> [How to customize the CMake build](./nxp_examples_freertos_platforms.md#how-to-customize-the-cmake-build)
> section.

### GN Build System

#### Building with Matter over Thread configuration on MCXW72

-   Build Matter-over-Thread configuration with BLE commissioning.

```
user@ubuntu:~/Desktop/git/connectedhomeip/examples/lighting-app/nxp/mcxw72$ gn gen out/debug
user@ubuntu:~/Desktop/git/connectedhomeip/examples/lighting-app/nxp/mcxw72$ ninja -C out/debug
```

#### General information

The resulting output file can be found in out/debug/chip-mcxw72-light-example.

Additional GN options can be added when building the application. You can check
[Common GN options to FreeRTOS platforms](./nxp_examples_freertos_platforms.md#general-information)
for the full list.

<a name="manufacturing-data"></a>

## Manufacturing data

See
[Guide for writing manufacturing data on NXP devices](./nxp_manufacturing_flow.md)

<a name="flashing-and-debugging"></a>

## Flashing and debugging

### Flashing the example application

We recommend using `JLink` from Segger to flash the example application. It can
be downloaded and installed from
https://www.segger.com/downloads/jlink. Once installed, JLink can
be run to flash the application using the following steps :

```
$ JLink
```

```
J-Link > connect
Device> ? # you will be presented with a dialog -> select `MCXW727`
Please specify target interface:
J) JTAG (Default)
S) SWD
T) cJTAG
TIF> S
Specify target interface speed [kHz]. <Default>: 4000 kHz
Speed> # <enter>
```

Program the application executable :

```
J-Link > loadfile <application_binary> (.srec format)
```

Program the NBU :

```
J-Link > loadbin <NBU_binary> 0x48800000
```

where `NBU_binary` can be found in the SDK at path:
`middleware/wireless/ieee-802.15.4/bin/mcxw72/mcxw72_nbu_ble_15_4_dyn.bin`

<a name="testing-the-example"></a>

## Testing the example

To test the example, please make sure to check the `Testing the example` section
from the common readme
[CHIP NXP Examples Guide for FreeRTOS platforms](./nxp_examples_freertos_platforms.md#testing-the-example).

### UART Ports

Testing the example with the CLI enabled will require connecting to both UART0
and UART1. For applications where CLI is _not_ available, connecting to the default
UART1 is enough.

| Interface | Role                                                                   |
| --------- | ---------------------------------------------------------------------- |
| UART0     | Used for logs only when `matter-cli` is enabled                        |
| UART1     | Used either for `matter-cli` or for logs when `matter-cli` is disabled |

You need a `USB-UART` bridge to make use of the UART0 interface. The pin
configuration depends on the type of board you are working on.

On a `NXP FRDM-MCXW72` board, the UART0 is available on the following pins:

-   `J1` (DL) `pin 1` - UART0 RX
-   `J1` (DL) `pin 2` - UART0 TX
-   `J2` (DH) `pin 4` - GND

On a `NXP MCXW72-EVK` board, the UART0 is available on the following pins:

-   `JP11 pin 1` - UART0 TX
-   `JP12 pin 1` - UART0 RX
-   `J11 pin 4` (on the side of the carrier board) - GND

### Device UI

The device state feedback is provided through the on-board LEDs:

| Widget  | Effect                              | Description                                                                                           |
| ------- | ----------------------------------- | ----------------------------------------------------------------------------------------------------- |
| LED2    | short flash on (50ms on/950ms off)  | The device is in an unprovisioned (unpaired) state and is waiting for a commissioner to connect.      |
| LED2    | rapid even flashing (100ms period)  | The device is in an unprovisioned state and a commissioner is connected via BLE.                      |
| LED2    | short flash off (950ms on/50ms off) | The device is fully provisioned, but does not yet have full network (Thread) or service connectivity. |
| LED2    | solid on                            | The device is fully provisioned and has full network and service connectivity.                        |
| RGB LED | on                                  | The `StateValue` attribute of the `BooleanState` cluster is `true` (simulating detection).            |
| RGB LED | off                                 | The `StateValue` attribute of the `BooleanState` cluster is `false` (simulating no detection).        |

The user can control the device using the on-board buttons. The actions are summarized below:

| Button | Action       | State                                        | Output                                                                                                                                 |
| ------ | ------------ | -------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| SW2    | short press  | not commissioned                             | Enable/disable BLE advertising                                                                                                                 |
| SW2    | long press   | any                                          | Initiate a factory reset (can be cancelled by pressing the button again within the factory reset timeout limit - 6 seconds by default) |
| SW3    | short press  | any                                          | Toggle attribute `StateValue` value                                                                                                    |
| SW3    | long press   | any                                          | Clean soft reset of the device (takes into account proper Matter shutdown procedure)                                                   |

<a name="ota-software-update"></a>

## OTA Software Update

Over-The-Air software updates are supported with the MCXW72 examples. The
process to follow in order to perform a software update is described in the
dedicated guide
['Matter Over-The-Air Software Update with NXP MCXW72 example applications'](./nxp_mcxw71_ota_guide.md).
