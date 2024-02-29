/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/common/CBitStream.h
 *  PURPOSE:     Network bitstream class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "../CCommon.h"

class CBitStream
{
public:
    CBitStream(const void* pData = nullptr, std::uint32_t uiDataSize = 0, bool bCopyData = false) noexcept
    {
        pBitStream = g_pNetServer->AllocateNetServerBitStream(0, pData, uiDataSize, bCopyData);
    }
    ~CBitStream() noexcept { g_pNetServer->DeallocateNetServerBitStream((NetBitStreamInterface*)pBitStream); };
    NetBitStreamInterfaceNoVersion* operator->() noexcept { return pBitStream; }

    NetBitStreamInterfaceNoVersion* pBitStream;
};

// Use this if Version() is required - Make sure the player is the once receiving/sending the data
class CPlayerBitStream
{
public:
    CPlayerBitStream(class CPlayer* pPlayer) noexcept;            //  { pBitStream = g_pNetServer->AllocateNetServerBitStream ( pPlayer->GetBitStreamVersion() ); };
    ~CPlayerBitStream() noexcept {
        g_pNetServer->DeallocateNetServerBitStream(pBitStream);
    }
    NetBitStreamInterface* operator->() noexcept { return pBitStream; }

    NetBitStreamInterface* pBitStream;
};
