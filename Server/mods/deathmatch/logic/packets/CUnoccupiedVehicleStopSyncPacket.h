/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/packets/CUnoccupiedVehicleStopSyncPacket.h
 *  PURPOSE:     Unoccupied vehicle stop synchronization packet class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CPacket.h"

class CUnoccupiedVehicleStopSyncPacket final : public CPacket
{
public:
    CUnoccupiedVehicleStopSyncPacket(ElementID ID) noexcept { m_ID = ID; };

    ePacketID     GetPacketID() const noexcept { return PACKET_ID_UNOCCUPIED_VEHICLE_STOPSYNC; }
    std::uint32_t GetFlags() const noexcept { return PACKET_HIGH_PRIORITY | PACKET_RELIABLE | PACKET_SEQUENCED; }

    bool Write(NetBitStreamInterface& BitStream) const noexcept
    {
        BitStream.Write(m_ID);
        return true;
    }

private:
    ElementID m_ID;
};
