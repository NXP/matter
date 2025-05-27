# Matter NXP Contact Sensor Example Application

- [Overview](#overview)
- [Supported Platforms](#supported-platforms)
- [Data Model](#data-model)
- [Long Idle Time ICD Support](#long-idle-time-icd-support)
- [Low Power](#low-power)

<a name="overview"></a>

## Overview

This reference application implements a Contact Sensor device type. It uses
board buttons or `matter-cli` for user input and LEDs for state feedback. You
can use this example as a reference for creating your own application.

The example is based on
[Project CHIP](https://github.com/project-chip/connectedhomeip) and NXP SDK, and
provides a prototype application that demonstrates device commissioning and
different cluster control.

The contact sensor communicates with clients over a low-power, 802.15.4 Thread network.

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

The Contact Sensor example is supported on the following platforms :

| NXP platform        | Dedicated readme                                                             |
| ------------------- | ---------------------------------------------------------------------------- |
| MCXW71              | [NXP MCXW71 Guide](../../../docs/platforms/nxp/nxp_mcxw71_guide.md)          |
| MCXW72              | [NXP MCXW72 Guide](../../../docs/platforms/nxp/nxp_mcxw72_guide.md)          |

For details on platform-specific requirements and configurations, please refer
to the respective platform's readme.

A list of all available standard contact sensor app build targets is presented below.

| Target name                                                  | Description                                                                                 |
| ------------------------------------------------------------ | ------------------------------------------------------------------------------------------- |
| `nxp-device-freertos-contact-sensor-low-power`               | Default low-power contact sensor                                                            |
| `nxp-device-freertos-contact-sensor-low-power-factory`       | Default low-power contact sensor with factory data                                          |
| `nxp-device-freertos-contact-sensor-low-power-lit`           | Low-power contact sensor as LIT ICD                                                         |
| `nxp-device-freertos-contact-sensor-low-power-sw-v2`         | Low-power contact sensor with software version 2 (can be used to test OTA)                  |
| `nxp-device-freertos-contact-sensor-low-power-factory-sw-v2` | Low-power contact sensor with factory data and software version 2 (can be used to test OTA) |

where `device` is be one of the [supported platforms](#supported-platforms).

<a name="data-model"></a>

## Data Model

There are two available data models that can be used by the application:

| Path                             | Description                    |
| -------------------------------- | ------------------------------ |
| `zap-lit/contact-sensor-app.zap` | Data model for LIT ICD support |
| `zap-sit/contact-sensor-app.zap` | Data model for SIT ICD support |

The selection is done automatically by the build system based on the ICD
configuration.

The data model can be changed by simply replacing the gn `deps` statement
corresponding to data model target.

<a name="long-idle-time-icd-support"></a>

## Long Idle Time ICD Support

By default, the application is compiled as a SIT ICD (Short Idle Time
Intermittently Connected Device).

The following is a list of ICD configuration _gn_ args.

| gn arg                                         | Default value | Description                                                                                                |
| ---------------------------------------------- | ------------- | ---------------------------------------------------------------------------------------------------------- |
| `nxp_ot_idle_interval_ms`                      | 2000 (ms)     | OT Idle Interval duration                                                                                  |
| `nxp_ot_active_interval_ms`                    | 500 (ms)      | OT Active Interval duration                                                                                |
| `nxp_idle_mode_duration_s`                     | 600 (s)       | Idle Mode Interval duration                                                                                |
| `nxp_active_mode_duration_ms`                  | 10000 (ms)    | Active Mode Interval duration                                                                              |
| `nxp_active_mode_threshold_ms`                 | 1000 (ms)     | Active Mode Threshold value                                                                                |
| `nxp_icd_supported_clients_per_fabric`         | 2             | Registration slots per fabric                                                                              |
| `chip_enable_icd_lit`                          | false         | Enable LIT ICD support                                                                                     |
| `chip_enable_icd_dsls`                         | false         | Enable LIT ICD DSLS support                                                                                |
| `chip_persist_subscriptions`                   | true          | Try once to re-establish subscriptions from the server side after reboot. May be disabled for LIT use case |
| `chip_subscription_timeout_resumption`         | true          | Same as above, but try to re-establish timeout out subscriptions using `Fibonacci Backoff` for retries pacing. May be disabled for LIT use case |

If LIT ICD support is needed then `chip_enable_icd_lit=true` must be specified
as gn argument and the above parameters must be modified to comply with LIT
requirements (e.g.: LIT devices must configure
`chip_ot_idle_interval_ms > 15000`). Example LIT configuration:

```
nxp_ot_idle_interval_ms = 15000           # 15s Idle Intervals
nxp_ot_active_interval_ms = 500           # 500ms Active Intervals
nxp_idle_mode_duration_s = 3600           # 60min Idle Mode Interval
nxp_active_mode_duration_ms = 0           # 0 Active Mode Interval
nxp_active_mode_threshold_ms = 30000      # 30s Active Mode Threshold
```

<a name="low-power"></a>

## Low Power

The example also offers the possibility to run in low power mode. This means
that the board will go in deep sleep most of the time and the power consumption
will be very low.

In order to build with low power support, the following _gn_ args must be used:

```
nxp_use_low_power = true
chip_openthread_ftd = false
nxp_enable_ot_cli = false
chip_logging = false
```

In order to maintain a low power consumption, the UI LEDs are disabled. Console
logs can be used instead, but it might affect low power timings. Also, please
note that once the application is flashed onto the board the debugger might disconnect
because the board enters low power.
