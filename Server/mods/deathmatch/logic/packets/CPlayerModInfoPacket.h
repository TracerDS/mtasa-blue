/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/packets/CPlayerModInfoPacket.h
 *  PURPOSE:
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CPacket.h"

struct SModInfoItem
{
    std::uint16_t usId;
    std::uint32_t uiHash;
    SString       strName;
    bool          bHasSize;
    CVector       vecSize;
    CVector       vecOriginalSize;
    bool          bHasHashInfo;
    std::uint32_t uiShortBytes;
    SString       strShortMd5;
    SString       strShortSha256;
    std::uint32_t uiLongBytes;
    SString       strLongMd5;
    SString       strLongSha256;
};

class CPlayerModInfoPacket final : public CPacket
{
public:
    ePacketID     GetPacketID() const noexcept { return PACKET_ID_PLAYER_MODINFO; }
    std::uint32_t GetFlags() const noexcept { return 0; }            // Not used

    bool Read(NetBitStreamInterface& BitStream) noexcept;

    SString                   m_strInfoType;
    std::vector<SModInfoItem> m_ModInfoItemList;
};
