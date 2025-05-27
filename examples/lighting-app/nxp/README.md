# Matter NXP Lighting Example Application

- [Overview](#overview)
- [Supported Platforms](#supported-platforms)
- [Data Model](#data-model)
- [LED PWM](#led-pwm)

<a name="overview"></a>

## Overview

This reference application implements an On/Off Light device type. It uses board
buttons or `matter-cli` for user input and LEDs for state feedback. You can use
this example as a reference for creating your own application.

The example is based on
[Project CHIP](https://github.com/project-chip/connectedhomeip) and NXP SDK, and
provides a prototype application that demonstrates device commissioning and
different cluster control.

The light bulb device communicates with clients over a low-power, 802.15.4 Thread network.

It can be commissioned into an existing Matter network using a controller such
as `chip-tool`.

This example implements a `User-Intent Commissioning Flow`, meaning that the user
has to press a button in order for the device to be ready for commissioning. The
initial commissioning is done through `ble-thread` pairing method.

The Thread network dataset will be transferred on the device using a secure
session over Bluetooth LE. In order to start the commissioning process, the user
must enable BLE advertising on the device manually. To pair successfully, the
commissioner must know the commissioning information corresponding to the
device: setup passcode and discriminator. This data is usually encoded within a
QR code or printed to the device's UART console.

<a name="supported-platforms"></a>

## Supported Platforms

The On/Off Light example is supported on the following platforms:

| NXP platform        | Dedicated readme                                                             |
| ------------------- | ---------------------------------------------------------------------------- |
| MCXW71              | [NXP MCXW71 Guide](../../../docs/platforms/nxp/nxp_mcxw71_guide.md)          |
| MCXW72              | [NXP MCXW72 Guide](../../../docs/platforms/nxp/nxp_mcxw72_guide.md)          |

For details on platform-specific requirements and configurations, please refer
to the respective platform's readme.

A list of all available contact sensor targets can be viewed in the following
table:

| Target name                                           | Description                                                                     |
| ----------------------------------------------------- | ------------------------------------------------------------------------------- |
| `nxp-device-freertos-lighting`                        | Default lighting app                                                            |
| `nxp-device-freertos-lighting-factory`                | Default lighting app with factory data                                          |
| `nxp-device-freertos-lighting-rotating-id`            | Lighting app with rotating device id support                                    |
| `nxp-device-freertos-lighting-factory-dac-conversion` | Lighting app that leverages a secure enclave to secure the DAC private key      |
| `nxp-device-freertos-lighting-sw-v2`                  | Lighting app with software version 2 (can be used to test OTA)                  |
| `nxp-device-freertos-lighting-factory-sw-v2`          | Lighting app with factory data and software version 2 (can be used to test OTA) |

where `device` is be one of the [supported platforms](#supported-platforms).

<a name="data-model"></a>

## Data Model

The application uses an NXP specific data model file:

| Path                      | Description                             |
| ------------------------- | --------------------------------------- |
| `zap/lighting-on-off.zap` | Data model for On/Off Light device type |

The data model can be changed by simply replacing the gn `deps` statement
corresponding to data model target.

<a name="led-pwm"></a>

## LED PWM

In the default configuration, the onboard RGB LED pins are configured as GPIO
pins. In order to enable the dimming feature, the pins need to be configured in
PWM mode and synchronizeded with channels of the `TPM` (Timer PWM Module). To enable
this feature, the application needs to be compiled using the `nxp_config_dimmable_led=true`
option.

If the feature is enabled, the LED brightness can be controlled using
`LevelControl` [cluster commands](../../../docs/development_controllers/chip-tool/chip_tool_guide.md#step-7-control-application-data-model-clusters).
