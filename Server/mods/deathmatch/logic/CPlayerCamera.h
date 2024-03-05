/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CPlayerCamera.h
 *  PURPOSE:     Player camera entity class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include <CVector.h>

class CPlayer;
class CElement;

enum eCameraMode
{
    CAMERAMODE_PLAYER = 0,
    CAMERAMODE_FIXED,
    CAMERAMODE_INVALID,
};

class CPlayerCamera
{
public:
    CPlayerCamera(CPlayer* pPlayer) noexcept;
    ~CPlayerCamera() noexcept;

    eCameraMode GetMode() const { return m_Mode; }
    void        SetMode(eCameraMode Mode);

    const CVector& GetPosition() const;
    void           GetPosition(CVector& vecPosition) const;
    void           SetPosition(const CVector& vecPosition);

    void GetLookAt(CVector& vecLookAt) const;
    void SetLookAt(const CVector& vecLookAt);

    void SetMatrix(const CVector& vecPosition, const CVector& vecLookAt);

    CElement* GetTarget() const noexcept { return m_pTarget; }
    void      SetTarget(CElement* pElement);

    float GetRoll() const noexcept { return m_fRoll; }
    void  SetRoll(float fRoll) noexcept { m_fRoll = fRoll; }
    float GetFOV() const noexcept { return m_fFOV; }
    void  SetFOV(float fFOV) noexcept { m_fFOV = fFOV; }

    void SetRotation(CVector& vecRotation);

    std::uint8_t GetInterior() const noexcept { return m_ucInterior; }
    void         SetInterior(std::uint8_t ucInterior) noexcept { m_ucInterior = ucInterior; }

    CPlayer* GetPlayer() const noexcept { return m_pPlayer; }

    std::uint8_t GenerateSyncTimeContext();
    bool  CanUpdateSync(std::uint8_t ucRemote);

private:
    CPlayer*      m_pPlayer;
    eCameraMode   m_Mode;
    float         m_fRotation;
    std::uint8_t  m_ucInterior;
    CVector       m_vecPosition;
    CVector       m_vecLookAt;
    CElement*     m_pTarget;
    float         m_fRoll;
    float         m_fFOV;
    std::uint8_t  m_ucSyncTimeContext;
};
