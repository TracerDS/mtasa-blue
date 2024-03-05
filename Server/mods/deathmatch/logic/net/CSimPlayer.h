/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CPad.h"

struct SSimVehicleDamageInfo
{
    SFixedArray<std::uint8_t, MAX_DOORS>  m_ucDoorStates;
    SFixedArray<std::uint8_t, MAX_WHEELS> m_ucWheelStates;
    SFixedArray<std::uint8_t, MAX_PANELS> m_ucPanelStates;
    SFixedArray<std::uint8_t, MAX_LIGHTS> m_ucLightStates;
};

//
// Copy of enough data from CPlayer to enable autonomous relaying of pure sync packets
//
class CSimPlayer
{
public:
    ZERO_ON_NEW
    CSimPlayer() noexcept { DEBUG_CREATE_COUNT("CSimPlayer"); }
    ~CSimPlayer() noexcept { DEBUG_DESTROY_COUNT("CSimPlayer"); }

    const std::multimap<std::uint16_t, CSimPlayer*>& GetPuresyncSendList();

    bool               IsJoined() const noexcept { return m_bIsJoined; };
    std::uint16_t      GetBitStreamVersion() const noexcept { return m_usBitStreamVersion; };
    NetServerPlayerID& GetSocket() noexcept { return m_PlayerSocket; };

    // General synced vars
    bool                               m_bIsJoined;
    std::uint16_t                      m_usBitStreamVersion;
    NetServerPlayerID                  m_PlayerSocket;
    std::vector<CSimPlayer*>           m_PuresyncSendListFlat;
    std::multimap<std::uint16_t, CSimPlayer*> m_PuresyncSendListGrouped;            // Send list grouped by bitstream version
    bool                               m_bSendListChanged;
    bool                               m_bHasOccupiedVehicle;
    bool                               m_bIsExitingVehicle;
    CControllerState                   m_sharedControllerState;            // Updated by CSim*Packet code

    // Used in CSimPlayerPuresyncPacket and CSimVehiclePuresyncPacket
    ElementID m_PlayerID;
    std::uint16_t m_usLatency;
    std::uint8_t  m_ucSyncTimeContext;
    std::uint8_t  m_ucWeaponType;

    // Used in CSimVehiclePuresyncPacket
    std::uint16_t         m_usVehicleModel;
    std::uint8_t          m_ucOccupiedVehicleSeat;
    float                 m_fWeaponRange;
    std::uint32_t         m_uiVehicleDamageInfoSendPhase;
    SSimVehicleDamageInfo m_VehicleDamageInfo;

    // Used in CSimKeysyncPacket
    bool m_bVehicleHasHydraulics;
    bool m_bVehicleIsPlaneOrHeli;

    // Flag
    bool m_bDoneFirstUpdate;

    // Interlink to CPlayer object
    CPlayer* m_pRealPlayer;
};
