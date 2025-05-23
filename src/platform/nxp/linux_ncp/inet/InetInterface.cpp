/*
 *
 *    Copyright (c) 2020-2022 Project CHIP Authors
 *    Copyright (c) 2019 Google LLC.
 *    Copyright (c) 2013-2017 Nest Labs, Inc.
 *    Copyright 2025 NXP
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
 *      Implementation of network interface abstraction layer.
 *
 */
#include <inet/InetInterface.h>
#include <inet/IPPrefix.h>
#include <lib/support/CHIPMem.h>
#include <lib/support/CHIPMemString.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/DLLUtil.h>
#include <lib/support/SafeInt.h>

#if CHIP_SYSTEM_CONFIG_USE_NCP
extern "C" {
#include "ncp_wifi_api.h"
}
extern ncp_netif ncp_netif_list;
#endif

#include <stdio.h>
#include <string.h>

namespace chip {
namespace Inet {

#if CHIP_SYSTEM_CONFIG_USE_NCP

InterfaceIterator::InterfaceIterator(void)
{
    mCurNetif = &ncp_netif_list;
}

bool InterfaceIterator::HasCurrent(void)
{
    if (strncmp(wlan_ncp_get_state(), "COMPLETED", 9))
    {
        ChipLogProgress(DeviceLayer, "Inet Get connect state not connect.\r\n");
        return false;
    }
    return mCurNetif != NULL;
}

InterfaceId InterfaceIterator::GetInterfaceId(void)
{
    return InterfaceId(mCurNetif);
}

CHIP_ERROR InterfaceId::GetInterfaceName(char * nameBuf, size_t nameBufSize) const
{
    if (mPlatformInterface)
    {
        int status = snprintf(nameBuf, nameBufSize, "%s", "ncp_mlan");

        if (status >= static_cast<int>(nameBufSize)){
            return CHIP_ERROR_BUFFER_TOO_SMALL;
        }

        return CHIP_NO_ERROR;
    }
    if (nameBufSize < 1)
    {
        return CHIP_ERROR_BUFFER_TOO_SMALL;
    }
    nameBuf[0] = 0;

    return CHIP_NO_ERROR;
}

CHIP_ERROR InterfaceId::InterfaceNameToId(const char * intfName, InterfaceId & interface)
{
    if (strlen(intfName) < 8)
    {
        return INET_ERROR_UNKNOWN_INTERFACE;
    }
    
    if(strcmp(intfName, "ncp_mlan") == 0)
    {
        interface = InterfaceId(&ncp_netif_list);
        return CHIP_NO_ERROR;
    }

    return INET_ERROR_UNKNOWN_INTERFACE;
}

bool InterfaceIterator::Next()
{
    mCurNetif = mCurNetif->next;
    if(mCurNetif != nullptr)
    {
        return true;
    }

    return false;
}

CHIP_ERROR InterfaceIterator::GetInterfaceName(char * nameBuf, size_t nameBufSize)
{
    VerifyOrReturnError(HasCurrent(), CHIP_ERROR_INCORRECT_STATE);
    return InterfaceId(mCurNetif).GetInterfaceName(nameBuf, nameBufSize);
}

bool InterfaceIterator::IsUp()
{
    return HasCurrent() && netif_is_up(mCurNetif);
}

bool InterfaceIterator::SupportsMulticast()
{
    return HasCurrent() && (mCurNetif->flags & (NETIF_FLAG_IGMP | NETIF_FLAG_MLD6 | NETIF_FLAG_BROADCAST)) != 0;
}

bool InterfaceIterator::HasBroadcastAddress()
{
    return HasCurrent() && (mCurNetif->flags & NETIF_FLAG_BROADCAST) != 0;
}

CHIP_ERROR InterfaceIterator::GetInterfaceType(InterfaceType & type)
{
    return CHIP_ERROR_NOT_IMPLEMENTED;
}

CHIP_ERROR InterfaceIterator::GetHardwareAddress(uint8_t * addressBuffer, uint8_t & addressSize, uint8_t addressBufferSize)
{
    VerifyOrReturnError(addressBuffer != nullptr, CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(HasCurrent(), CHIP_ERROR_INCORRECT_STATE);
    VerifyOrReturnError(addressBufferSize >= mCurNetif->hwaddr_len, CHIP_ERROR_BUFFER_TOO_SMALL);
    addressSize = mCurNetif->hwaddr_len;
    memcpy(addressBuffer, mCurNetif->hwaddr, addressSize);
    return CHIP_NO_ERROR;
}

bool InterfaceAddressIterator::HasCurrent()
{
    return mIntfIter.HasCurrent() && ((mCurAddrIndex != kBeforeStartIndex) || Next());
}

bool InterfaceAddressIterator::Next()
{
    mCurAddrIndex++;

    while (mIntfIter.HasCurrent())
    {
        struct ncp_netif_t * curIntf = mIntfIter.GetInterfaceId().GetPlatformInterface();

        while (mCurAddrIndex < CONFIG_MAX_IPV6_ADDRESSES)
        {
            if (ip6_addr_isvalid(netif_ip6_addr_state(curIntf, mCurAddrIndex)))
            {
                return true;
            }
            mCurAddrIndex++;
        }

#if INET_CONFIG_ENABLE_IPV4 && LWIP_IPV4
        if (mCurAddrIndex == CONFIG_MAX_IPV6_ADDRESSES)
        {
            if (!ip4_addr_isany(netif_ip4_addr(curIntf)))
            {
                return true;
            }
        }
#endif // INET_CONFIG_ENABLE_IPV4 && LWIP_IPV4

        mIntfIter.Next();
        mCurAddrIndex = 0;
    }

    return false;
}

CHIP_ERROR InterfaceAddressIterator::GetAddress(IPAddress & outIPAddress)
{
    if (!HasCurrent())
    {
        return CHIP_ERROR_SENTINEL;
    }

    struct ncp_netif_t * curIntf = mIntfIter.GetInterfaceId().GetPlatformInterface();

    if (mCurAddrIndex < CONFIG_MAX_IPV6_ADDRESSES)
    {
        const ip6_addr_t *lwip_ip6 = netif_ip6_addr(curIntf, mCurAddrIndex);
        struct in6_addr socket_in6;
        memcpy(socket_in6.s6_addr, lwip_ip6->addr, 16);
        outIPAddress = IPAddress(socket_in6);
        return CHIP_NO_ERROR;
    }
#if INET_CONFIG_ENABLE_IPV4 && LWIP_IPV4
    const ip4_addr_t *lwip_ip4 = netif_ip4_addr(curIntf);
    struct in_addr socket_inaddr;
    socket_inaddr.s_addr = lwip_ip4->addr;
    outIPAddress = IPAddress(socket_inaddr);
    return CHIP_NO_ERROR;
#else
    return CHIP_ERROR_INTERNAL;
#endif // INET_CONFIG_ENABLE_IPV4 && LWIP_IPV4
}

uint8_t InterfaceAddressIterator::GetPrefixLength()
{
    if (HasCurrent())
    {
        if (mCurAddrIndex < CONFIG_MAX_IPV6_ADDRESSES)
        {
            return 64;
        }
#if INET_CONFIG_ENABLE_IPV4 && LWIP_IPV4
        struct ncp_netif_t * curIntf = mIntfIter.GetInterfaceId().GetPlatformInterface();
        return NetmaskToPrefixLength((const uint8_t *) netif_ip4_netmask(curIntf), 4);
#endif // INET_CONFIG_ENABLE_IPV4 && LWIP_IPV4
    }
    return 0;
}

InterfaceId InterfaceAddressIterator::GetInterfaceId()
{
    return HasCurrent() ? mIntfIter.GetInterfaceId() : InterfaceId::Null();
}

CHIP_ERROR InterfaceAddressIterator::GetInterfaceName(char * nameBuf, size_t nameBufSize)
{
    VerifyOrReturnError(HasCurrent(), CHIP_ERROR_INCORRECT_STATE);
    return mIntfIter.GetInterfaceName(nameBuf, nameBufSize);
}

bool InterfaceAddressIterator::IsUp()
{
    return HasCurrent() && mIntfIter.IsUp();
}

bool InterfaceAddressIterator::SupportsMulticast()
{
    return HasCurrent() && mIntfIter.SupportsMulticast();
}

bool InterfaceAddressIterator::HasBroadcastAddress()
{
    return HasCurrent() && mIntfIter.HasBroadcastAddress();
}

CHIP_ERROR InterfaceId::GetLinkLocalAddr(IPAddress * llAddr) const
{
    VerifyOrReturnError(llAddr != nullptr, CHIP_ERROR_INVALID_ARGUMENT);

#if !LWIP_IPV6
    return CHIP_ERROR_NOT_IMPLEMENTED;
#endif //! LWIP_IPV6

    for (struct ncp_netif_t * intf = &ncp_netif_list; intf != nullptr; intf = intf->next)
    {
        if ((mPlatformInterface != nullptr) && (mPlatformInterface != intf))
            continue;
        for (int j = 0; j < CONFIG_MAX_IPV6_ADDRESSES; ++j)
        {
            if (ip6_addr_isvalid(netif_ip6_addr_state(intf, j)) && ip6_addr_islinklocal(netif_ip6_addr(intf, j)))
            {
                const ip6_addr_t *lwip_ip6 = netif_ip6_addr(intf, j);
                struct in6_addr socket_in6;
                memcpy(socket_in6.s6_addr, lwip_ip6->addr, 16);
                (*llAddr) = IPAddress(socket_in6);
                return CHIP_NO_ERROR;
            }
        }
        if (mPlatformInterface != nullptr)
        {
            return INET_ERROR_ADDRESS_NOT_FOUND;
        }
    }
    return CHIP_NO_ERROR;
}
#endif

// static
InterfaceId InterfaceId::FromIPAddress(const IPAddress & addr)
{
    InterfaceAddressIterator addrIter;

    for (; addrIter.HasCurrent(); addrIter.Next())
    {
        IPAddress curAddr;
        if ((addrIter.GetAddress(curAddr) == CHIP_NO_ERROR) && (addr == curAddr))
        {
            return addrIter.GetInterfaceId();
        }
    }

    return InterfaceId::Null();
}

// static
bool InterfaceId::MatchLocalIPv6Subnet(const IPAddress & addr)
{
    if (addr.IsIPv6LinkLocal())
        return true;

    InterfaceAddressIterator ifAddrIter;
    for (; ifAddrIter.HasCurrent(); ifAddrIter.Next())
    {
        IPPrefix addrPrefix;
        if (ifAddrIter.GetAddress(addrPrefix.IPAddr) != CHIP_NO_ERROR)
            continue;
#if INET_CONFIG_ENABLE_IPV4
        if (addrPrefix.IPAddr.IsIPv4())
            continue;
#endif // INET_CONFIG_ENABLE_IPV4
        if (addrPrefix.IPAddr.IsIPv6LinkLocal())
            continue;
        addrPrefix.Length = ifAddrIter.GetPrefixLength();
        if (addrPrefix.MatchAddress(addr))
            return true;
    }

    return false;
}

uint8_t NetmaskToPrefixLength(const uint8_t * netmask, uint16_t netmaskLen)
{
    uint8_t prefixLen = 0;

    for (uint16_t i = 0; i < netmaskLen; i++, prefixLen = static_cast<uint8_t>(prefixLen + 8u))
    {
        uint8_t b = netmask[i];
        if (b != 0xFF)
        {
            if ((b & 0xF0) == 0xF0)
                prefixLen = static_cast<uint8_t>(prefixLen + 4u);
            else
                b = static_cast<uint8_t>(b >> 4);

            if ((b & 0x0C) == 0x0C)
                prefixLen = static_cast<uint8_t>(prefixLen + 2u);
            else
                b = static_cast<uint8_t>(b >> 2);

            if ((b & 0x02) == 0x02)
                prefixLen++;

            break;
        }
    }

    return prefixLen;
}

} // namespace Inet
} // namespace chip