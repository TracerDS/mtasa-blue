/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/packets/CVehicleInOutPacket.h
 *  PURPOSE:     Vehicle enter/exit synchronization packet class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CPacket.h"
#include <CVector.h>

class CVehicleInOutPacket final : public CPacket
{
public:
    CVehicleInOutPacket() noexcept;
    CVehicleInOutPacket(ElementID PedID, ElementID VehicleID, std::uint8_t ucSeat, std::uint8_t ucAction) noexcept;
    CVehicleInOutPacket(ElementID PedID, ElementID VehicleID, std::uint8_t ucSeat, std::uint8_t ucAction, std::uint8_t ucDoor) noexcept;
    CVehicleInOutPacket(ElementID PedID, ElementID VehicleID, std::uint8_t ucSeat, std::uint8_t ucAction, ElementID PedIn, ElementID PedOut) noexcept;
    virtual ~CVehicleInOutPacket() noexcept;

    ePacketID     GetPacketID() const noexcept { return PACKET_ID_VEHICLE_INOUT; };
    std::uint32_t GetFlags() const noexcept { return PACKET_HIGH_PRIORITY | PACKET_RELIABLE | PACKET_SEQUENCED; };

    bool Read(NetBitStreamInterface& BitStream) noexcept;
    bool Write(NetBitStreamInterface& BitStream) const noexcept;

    std::uint8_t  GetDoor() const noexcept { return m_ucDoor; };
    bool          GetOnWater() const noexcept { return m_bOnWater; };
    ElementID     GetVehicleID() const noexcept { return m_VehicleID; };
    ElementID     GetPedID() const noexcept { return m_PedID; };
    std::uint8_t  GetSeat() const noexcept { return m_ucSeat; };
    float         GetDoorAngle() const noexcept { return m_fDoorAngle; }
    std::uint8_t  GetAction() const noexcept { return m_ucAction; };
    ElementID     GetPedIn() const noexcept { return m_PedIn; };
    ElementID     GetPedOut() const noexcept { return m_PedOut; };
    std::uint8_t  GetStartedJacking() const noexcept { return m_ucStartedJacking; };

    void SetPedID(ElementID ID) noexcept { m_PedID = ID; };
    void SetVehicleID(ElementID ID) noexcept { m_VehicleID = ID; };
    void SetSeat(std::uint8_t ucSeat) noexcept { m_ucSeat = ucSeat; };
    void SetDoor(std::uint8_t ucDoor) noexcept { m_ucDoor = ucDoor; }
    void SetDoorAngle(float fDoorAngle) noexcept { m_fDoorAngle = fDoorAngle; }
    void SetAction(std::uint8_t ucAction) noexcept { m_ucAction = ucAction; };
    void SetPedIn(ElementID PedIn) noexcept { m_PedIn = PedIn; };
    void SetPedOut(ElementID PedOut) noexcept { m_PedOut = PedOut; };
    void SetFailReason(std::uint8_t ucReason) noexcept { m_ucFailReason = ucReason; }
    void SetCorrectVector(const CVector& vector) noexcept {
        m_pCorrectVector = new CVector(vector.fX, vector.fY, vector.fZ);
    }

private:
    ElementID     m_PedID;                       // The ped
    ElementID     m_VehicleID;                   // The vehicle
    std::uint8_t  m_ucSeat;                      // The seat
    std::uint8_t  m_ucAction;                    // The action, see CGame.h
    ElementID     m_PedIn;                       // The ped jacking
    ElementID     m_PedOut;                      // The ped getting jacked
    std::uint8_t  m_ucStartedJacking;            // 1 = client reports he started jacking
    std::uint8_t  m_ucFailReason;                // eFailReasons
    CVector*      m_pCorrectVector;              // Ped position reported by client
    bool          m_bOnWater;                    // Vehicle in water reported by client
    std::uint8_t  m_ucDoor;                      // Door ID
    float         m_fDoorAngle;                  // Door angle
};
