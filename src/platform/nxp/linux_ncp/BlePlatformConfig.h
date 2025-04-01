/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


/**
 * Platform-specific configuration overrides for the CHIP BLE Layer on NCP platforms using the NCP SDK.
 *
 */

#pragma once

// ==================== Platform Adaptations ====================

struct bt_conn;

#ifndef BLE_CONNECTION_OBJECT
#define BLE_CONNECTION_OBJECT uint16_t
#endif // BLE_CONNECTION_OBJECT

#ifndef BLE_CONNECTION_UNINITIALIZED
#define BLE_CONNECTION_UNINITIALIZED (0xFFFF)
#endif // BLE_CONNECTION_UNINITIALIZED

#ifndef BLE_MAX_RECEIVE_WINDOW_SIZE
#define BLE_MAX_RECEIVE_WINDOW_SIZE 5
#endif // BLE_MAX_RECEIVE_WINDOW_SIZE

#ifndef CONFIG_BT_MAX_CONN
#define CONFIG_BT_MAX_CONN 1
#endif // CONFIG_BT_MAX_CONN

#ifndef CHIP_DEVICE_BLE_ADVERTISING_PRIORITY
/// Priority of the Matter BLE advertising when there are multiple application
/// components that compete for the BLE advertising.
#define CHIP_DEVICE_BLE_ADVERTISING_PRIORITY 0
#endif // CHIP_DEVICE_BLE_ADVERTISING_PRIORITY

// ========== Platform-specific Configuration Overrides =========

#ifndef LOG_MODULE_DECLARE
#define LOG_MODULE_DECLARE(...)
#endif // LOG_MODULE_DECLARE

#ifndef LOG_HEXDUMP_DBG
#define LOG_HEXDUMP_DBG(...)
#endif // LOG_HEXDUMP_DBG



/* none so far */
