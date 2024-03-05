/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/net/ns_playerid.h
 *  PURPOSE:     Net server player ID interface
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "../../../Shared/sdk/SharedUtil.Misc.h"

class SNetExtraInfo : public CRefCountable
{
protected:
    SNetExtraInfo(const SNetExtraInfo&);
    ~SNetExtraInfo() noexcept {}

    const SNetExtraInfo& operator=(const SNetExtraInfo&);

public:
    ZERO_ON_NEW
    SNetExtraInfo() noexcept {}

    bool m_bHasPing;
    std::uint32_t m_uiPing;
};

class NetServerPlayerID
{
protected:
    std::uint32_t m_uiBinaryAddress;
    std::uint16_t m_usPort;

public:
    NetServerPlayerID() noexcept
    {
        m_uiBinaryAddress = 0xFFFFFFFF;
        m_usPort = 0xFFFF;
    }

    NetServerPlayerID(std::uint32_t uiBinaryAddress, std::uint16_t usPort) noexcept
    {
        m_uiBinaryAddress = uiBinaryAddress;
        m_usPort = usPort;
    }

    ~NetServerPlayerID() noexcept {}

    friend inline int operator==(const NetServerPlayerID& left, const NetServerPlayerID& right) noexcept
    {
        return left.m_uiBinaryAddress == right.m_uiBinaryAddress && left.m_usPort == right.m_usPort;
    }

    friend inline int operator!=(const NetServerPlayerID& left, const NetServerPlayerID& right) noexcept
    {
        return ((left.m_uiBinaryAddress != right.m_uiBinaryAddress) || (left.m_usPort != right.m_usPort));
    }

    friend inline bool operator<(const NetServerPlayerID& left, const NetServerPlayerID& right) noexcept
    {
        return left.m_uiBinaryAddress < right.m_uiBinaryAddress || (left.m_uiBinaryAddress == right.m_uiBinaryAddress && left.m_usPort < right.m_usPort);
    }

    std::uint32_t GetBinaryAddress() const noexcept { return m_uiBinaryAddress; };
    std::uint16_t GetPort() const noexcept { return m_usPort; };
};
