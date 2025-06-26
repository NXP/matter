# Matter NXP Door Lock Example Application

- [Matter NXP Door Lock Example Application](#matter-nxp-door-lock-example-application)
  - [Overview](#overview)
  - [Supported Platforms](#supported-platforms)
  - [Environment Setup, Building, and Testing](#environment-setup-building-and-testing)
  - [Data Model](#data-model)
  - [MCXW Instructions](#mcxw-instructions)

<a name="overview"></a>

## Overview

The NXP Door Lock example is based on
[Project CHIP](https://github.com/project-chip/connectedhomeip) and NXP SDK, and
provides a prototype application that demonstrates device commissioning and
different cluster control.

<a name="supported-platforms"></a>

## Supported Platforms

The Door Lock example is supported on the following platforms :

| NXP platform        | Dedicated readme                                                             |
| ------------------- | ---------------------------------------------------------------------------- |
| MCXW71              | [NXP MCXW71 Guide](../../../docs/platforms/nxp/nxp_mcxw71_guide.md)          |
| MCXW72              | [NXP MCXW72 Guide](../../../docs/platforms/nxp/nxp_mcxw72_guide.md)          |
| RW61x (FreeRTOS OS) | [NXP RW61x (FreeRTOS) Guide](../../../docs/platforms/nxp/nxp_rw61x_guide.md) |

For details on platform-specific requirements and configurations, please refer
to the respective platform's readme.

## Environment Setup, Building, and Testing

All the information required to set up the environment, build the application,
and test it can be found in the common readme for NXP platforms :

-   NXP FreeRTOS Platforms : Refer to the
    [CHIP NXP Examples Guide for FreeRTOS platforms](../../../docs/platforms/nxp/nxp_examples_freertos_platforms.md)

<a name="data-model"></a>

## Data Model

The application uses an NXP specific data model file:

| Path               | Description                          |
| ------------------ | ------------------------------------ |
| `zap/lock-app.zap` | Data model for Door Lock device type |

The data model can be changed by simply replacing the gn `deps` statement
corresponding to data model target.

<a name="mcxw-instructions"></a>

## MCXW Instructions

This reference application implements an Door Lock device type. It uses board
buttons or `matter-cli` for user input and LEDs for state feedback. You can use
this example as a reference for creating your own application.

The door lock device communicates with clients over a low-power, 802.15.4 Thread
network.

It can be commissioned into an existing Matter network using a controller such
as `chip-tool`.

This example implements a `User-Intent Commissioning Flow`, meaning that the
user has to press a button in order for the device to be ready for
commissioning. The initial commissioning is done through `ble-thread` pairing
method.

The Thread network dataset will be transferred on the device using a secure
session over Bluetooth LE. In order to start the commissioning process, the user
must enable BLE advertising on the device manually. To pair successfully, the
commissioner must know the commissioning information corresponding to the
device: setup passcode and discriminator. This data is usually encoded within a
QR code or printed to the device's UART console.
