/*
 * Copyright 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

/* -------------------------------------------------------------------------- */
/*                           Includes                                         */
/* -------------------------------------------------------------------------- */
#include <platform/CHIPDeviceEvent.h>

/* -------------------------------------------------------------------------- */
/*                           Constants                                        */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                           Types                                            */
/* -------------------------------------------------------------------------- */

/** @brief This is a 'tentative' type and should be used as a pointer only */
struct bt_uuid {
	uint8_t type;
};

struct bt_uuid_16 {
	/** UUID generic type. */
	struct bt_uuid uuid;
	/** UUID value, 16-bit in host endianness. */
	uint16_t val;
};


#define BT_ADDR_SET_STATIC(a) ((a)->val[5] |= 0xc0)

/** @brief Initialize a 16-bit UUID.
 *
 *  @param value 16-bit UUID value in host endianness.
 */
#define BT_UUID_INIT_16(value)		\
{					\
	.uuid = { BT_UUID_TYPE_16 },	\
	.val = (value),			\
}

#define BT_DATA(_type, _data, _data_len) \
	{ \
		.type = (_type), \
		.data_len = (_data_len), \
		.data = (const uint8_t *)(_data), \
	}

/** @brief Bluetooth UUID types */
enum {
	/** UUID type 16-bit. */
	BT_UUID_TYPE_16,
	/** UUID type 32-bit. */
	BT_UUID_TYPE_32,
	/** UUID type 128-bit. */
	BT_UUID_TYPE_128,
};
