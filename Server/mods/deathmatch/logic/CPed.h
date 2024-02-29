/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CPed.h
 *  PURPOSE:     Ped entity class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CCommon.h"
#include "CElement.h"
#include "CPlayerClothes.h"
#include "CVehicle.h"
#include "CPlayerTasks.h"
#include <CMatrix.h>

#define INVALID_VEHICLE_SEAT 0xFF
#define NUM_PLAYER_STATS 343
#define WEAPON_SLOTS 13
#define STEALTH_KILL_RANGE 2.5f

enum ePedMoveAnim
{
    MOVE_DEFAULT = 0,
    MOVE_PLAYER = 54,
    MOVE_PLAYER_F,
    MOVE_PLAYER_M,
    MOVE_ROCKET,
    MOVE_ROCKET_F,
    MOVE_ROCKET_M,
    MOVE_ARMED,
    MOVE_ARMED_F,
    MOVE_ARMED_M,
    MOVE_BBBAT,
    MOVE_BBBAT_F,
    MOVE_BBBAT_M,
    MOVE_CSAW,
    MOVE_CSAW_F,
    MOVE_CSAW_M,
    MOVE_SNEAK,
    MOVE_JETPACK,
    MOVE_MAN = 118,
    MOVE_SHUFFLE,
    MOVE_OLDMAN,
    MOVE_GANG1,
    MOVE_GANG2,
    MOVE_OLDFATMAN,
    MOVE_FATMAN,
    MOVE_JOGGER,
    MOVE_DRUNKMAN,
    MOVE_BLINDMAN,
    MOVE_SWAT,
    MOVE_WOMAN,
    MOVE_SHOPPING,
    MOVE_BUSYWOMAN,
    MOVE_SEXYWOMAN,
    MOVE_PRO,
    MOVE_OLDWOMAN,
    MOVE_FATWOMAN,
    MOVE_JOGWOMAN,
    MOVE_OLDFATWOMAN,
    MOVE_SKATE,
};

inline bool IsValidMoveAnim(std::uint32_t iMoveAnim)
{
    return (iMoveAnim == MOVE_DEFAULT) || (iMoveAnim >= MOVE_PLAYER && iMoveAnim <= MOVE_JETPACK) || (iMoveAnim >= MOVE_MAN && iMoveAnim <= MOVE_SKATE);
}

enum eBone
{
    BONE_PELVIS1 = 1,
    BONE_PELVIS,
    BONE_SPINE1,
    BONE_UPPERTORSO,
    BONE_NECK,
    BONE_HEAD2,
    BONE_HEAD1,
    BONE_HEAD,
    BONE_RIGHTUPPERTORSO = 21,
    BONE_RIGHTSHOULDER,
    BONE_RIGHTELBOW,
    BONE_RIGHTWRIST,
    BONE_RIGHTHAND,
    BONE_RIGHTTHUMB,
    BONE_LEFTUPPERTORSO = 31,
    BONE_LEFTSHOULDER,
    BONE_LEFTELBOW,
    BONE_LEFTWRIST,
    BONE_LEFTHAND,
    BONE_LEFTTHUMB,
    BONE_LEFTHIP = 41,
    BONE_LEFTKNEE,
    BONE_LEFTANKLE,
    BONE_LEFTFOOT,
    BONE_RIGHTHIP = 51,
    BONE_RIGHTKNEE,
    BONE_RIGHTANKLE,
    BONE_RIGHTFOOT
};

struct CWeapon
{
    std::uint8_t  ucType = 0;
    std::uint16_t usAmmo = 0;
    std::uint16_t usAmmoInClip = 0;
};

class CPed : public CElement
{
    friend class CElement;

public:
    enum
    {
        VEHICLEACTION_NONE,
        VEHICLEACTION_ENTERING,
        VEHICLEACTION_EXITING,
        VEHICLEACTION_JACKING,
        VEHICLEACTION_JACKED,
    };

    CPed(class CPedManager* pPedManager, CElement* pParent, std::uint16_t usModel);
    ~CPed();
    CElement* Clone(bool* bAddEntity, CResource* pResource) override;

    bool IsEntity() const noexcept { return true; }

    virtual void Unlink();

    bool HasValidModel();

    bool          IsPlayer() const noexcept { return m_bIsPlayer; }
    std::uint16_t GetModel() const noexcept { return m_usModel; };
    void          SetModel(std::uint16_t usModel) noexcept { m_usModel = usModel; };

    bool IsDucked() const noexcept { return m_bDucked; };
    void SetDucked(bool bDucked) noexcept { m_bDucked = bDucked; };

    bool IsChoking() const noexcept { return m_bIsChoking; };
    void SetChoking(bool bChoking) noexcept { m_bIsChoking = bChoking; };

    bool IsWearingGoggles() const noexcept { return m_bWearingGoggles; };
    void SetWearingGoggles(bool bWearingGoggles) noexcept { m_bWearingGoggles = bWearingGoggles; };

    bool IsOnFire() const noexcept { return m_bIsOnFire; }
    void SetOnFire(bool bOnFire) noexcept { m_bIsOnFire = bOnFire; }

    CWeapon*      GetWeapon(std::uint8_t ucSlot = 0xFF) const noexcept;
    std::uint8_t  GetWeaponSlot() const noexcept { return m_ucWeaponSlot; }
    void          SetWeaponSlot(std::uint8_t ucSlot) noexcept;
    std::uint8_t  GetCurrentWeaponState() const noexcept { return m_ucCurrentWeaponState; };
    void          SetCurrentWeaponState(std::uint8_t ucWeaponState) noexcept { m_ucCurrentWeaponState = ucWeaponState; };
    std::uint8_t  GetWeaponType(std::uint8_t ucSlot = 0xFF) const noexcept;
    void          SetWeaponType(std::uint8_t ucType, std::uint8_t ucSlot = 0xFF) noexcept;
    std::uint16_t GetWeaponAmmoInClip(std::uint8_t ucSlot = 0xFF) const noexcept;
    void          SetWeaponAmmoInClip(std::uint16_t uscAmmoInClip, std::uint8_t ucSlot = 0xFF) noexcept;
    std::uint16_t GetWeaponTotalAmmo(std::uint8_t ucSlot = 0xFF) const noexcept;
    void          SetWeaponTotalAmmo(std::uint16_t usTotalAmmo, std::uint8_t ucSlot = 0xFF) noexcept;
    bool          HasWeaponType(std::uint8_t ucWeaponType) const noexcept;

    float GetMaxHealth() const noexcept;
    float GetHealth() const noexcept { return m_fHealth; }
    void  SetHealth(float fHealth) noexcept { m_fHealth = fHealth; }
    float GetArmor() const noexcept { return m_fArmor; }
    void  SetArmor(float fArmor) noexcept { m_fArmor = fArmor; }

    float GetPlayerStat(std::uint16_t usStat) const noexcept {
        return (usStat < NUM_PLAYER_STATS) ? m_fStats[usStat] : 0;
    }
    void  SetPlayerStat(std::uint16_t usStat, float fValue) noexcept
    {
        if (usStat >= NUM_PLAYER_STATS)
            return;
        m_fStats[usStat] = fValue;
    }

    CPlayerClothes* GetClothes() const noexcept { return m_pClothes; }

    static const char* GetBodyPartName(std::uint8_t ucID);

    bool HasJetPack() const noexcept { return m_bHasJetPack; }
    void SetHasJetPack(bool bHasJetPack) noexcept { m_bHasJetPack = bHasJetPack; }

    bool IsInWater() const noexcept { return m_bInWater; }
    void SetInWater(bool bInWater) noexcept { m_bInWater = bInWater; }

    bool IsOnGround() const noexcept { return m_bOnGround; }
    void SetOnGround(bool bOnGround) noexcept { m_bOnGround = bOnGround; }

    std::uint8_t GetAlpha() const noexcept { return m_ucAlpha; }
    void         SetAlpha(std::uint8_t ucAlpha) noexcept { m_ucAlpha = ucAlpha; }

    CPlayerTasks* GetTasks() const noexcept { return m_pTasks; }

    CElement* GetContactElement() const noexcept { return m_pContactElement; }
    void      SetContactElement(CElement* pElement) noexcept;

    void GetContactPosition(CVector& vecPosition) const noexcept { vecPosition = m_vecContactPosition; }
    void SetContactPosition(CVector& vecPosition) noexcept { m_vecContactPosition = vecPosition; }

    bool IsDead() const noexcept { return m_bIsDead; };
    void SetIsDead(bool bDead) noexcept;

    bool IsSpawned() const noexcept { return m_bSpawned; }
    void SetSpawned(bool bSpawned) noexcept { m_bSpawned = bSpawned; }

    float GetRotation() const noexcept { return m_fRotation; }
    void  SetRotation(float fRotation) noexcept { m_fRotation = fRotation; }

    void GetRotation(CVector& vecRotation) const noexcept;
    void GetMatrix(CMatrix& matrix) const noexcept;
    void SetMatrix(const CMatrix& matrix) noexcept;

    CElement* GetTargetedElement() const noexcept { return m_pTargetedEntity; }
    void      SetTargetedElement(CElement* pEntity) noexcept { m_pTargetedEntity = pEntity; }

    std::uint8_t GetFightingStyle() const noexcept { return m_ucFightingStyle; }
    void         SetFightingStyle(std::uint8_t ucStyle) noexcept { m_ucFightingStyle = ucStyle; }

    std::uint8_t GetMoveAnim() const noexcept { return static_cast<std::uint8_t>(m_iMoveAnim); }
    void         SetMoveAnim(int iMoveAnim) noexcept { m_iMoveAnim = iMoveAnim; }

    float GetGravity() const noexcept { return m_fGravity; }
    void  SetGravity(float fGravity) noexcept { m_fGravity = fGravity; }

    CVehicle*     GetOccupiedVehicle() const noexcept { return m_pVehicle; };
    std::uint32_t GetOccupiedVehicleSeat() const noexcept { return m_uiVehicleSeat; };
    CVehicle*     SetOccupiedVehicle(CVehicle* pVehicle, std::uint32_t uiSeat) noexcept;

    std::uint32_t GetVehicleAction() const noexcept { return m_uiVehicleAction; };
    void          SetVehicleAction(std::uint32_t uiAction) noexcept;

    bool IsAttachToable() const noexcept;

    CVector GetVelocity() const noexcept { return m_vecVelocity; };
    void GetVelocity(CVector& vecVelocity) const noexcept { vecVelocity = m_vecVelocity; };
    void SetVelocity(const CVector& vecVelocity) noexcept { m_vecVelocity = vecVelocity; };

    bool IsDoingGangDriveby() const noexcept { return m_bDoingGangDriveby; }
    void SetDoingGangDriveby(bool bDriveby) noexcept { m_bDoingGangDriveby = bDriveby; }

    bool IsHeadless() const noexcept { return m_bHeadless; };
    void SetHeadless(bool bHeadless) noexcept { m_bHeadless = bHeadless; };

    bool IsFrozen() const noexcept { return m_bFrozen; };
    void SetFrozen(bool bFrozen) noexcept { m_bFrozen = bFrozen; };

    CPlayer* GetSyncer() const noexcept { return m_pSyncer; };
    void     SetSyncer(CPlayer* pPlayer);

    bool     IsSyncable() const noexcept { return m_bSyncable; };
    void     SetSyncable(bool bSynced) noexcept { m_bSyncable = bSynced; };
    CPlayer* m_pSyncer;

    CVehicle* GetJackingVehicle() noexcept { return m_pJackingVehicle; }
    void      SetJackingVehicle(CVehicle* pVehicle) noexcept;

    bool IsStealthAiming() const noexcept { return m_bStealthAiming; }
    void SetStealthAiming(bool bAiming) noexcept { m_bStealthAiming = bAiming; }

    bool GetCollisionEnabled() const noexcept { return m_bCollisionsEnabled; }
    void SetCollisionEnabled(bool bCollisionEnabled) noexcept { m_bCollisionsEnabled = bCollisionEnabled; }

    std::int64_t GetLastFarSyncTick() const noexcept { return m_llLastFarSyncTick; }
    void         SetLastFarSyncTick(std::int64_t llLastSyncTick) noexcept { m_llLastFarSyncTick = llLastSyncTick; }

    void ClearNearPlayersList() noexcept { m_nearPlayersList.clear(); }
    void AddPlayerToNearList(CPlayer* pPlayer) noexcept { m_nearPlayersList.push_back(pPlayer); }
    bool IsNearPlayersListEmpty() const noexcept { return m_nearPlayersList.empty(); }

    std::vector<CPlayer*>& GetNearPlayers() noexcept { return m_nearPlayersList; }
    const std::vector<CPlayer*>& GetNearPlayers() const noexcept { return m_nearPlayersList; }

protected:
    bool ReadSpecialData(const int iLine) override;

protected:
    std::uint16_t                       m_usModel;
    CMatrix                              m_Matrix;
    bool                                 m_bDucked;
    bool                                 m_bIsChoking;
    bool                                 m_bWearingGoggles;
    bool                                 m_bIsOnFire;
    float                                m_fHealth;
    float                                m_fArmor;
    SFixedArray<float, NUM_PLAYER_STATS> m_fStats;
    CPlayerClothes*                      m_pClothes;
    bool                                 m_bHasJetPack;
    bool                                 m_bInWater;
    bool                                 m_bOnGround;
    bool                                 m_bIsPlayer;
    CPlayerTasks*                        m_pTasks;
    SFixedArray<CWeapon, WEAPON_SLOTS>   m_Weapons;
    std::uint8_t                        m_ucWeaponSlot;
    std::uint8_t                        m_ucCurrentWeaponState;
    std::uint8_t                        m_ucAlpha;
    CElement*                            m_pContactElement;
    CVector                              m_vecContactPosition;
    bool                                 m_bIsDead;
    float                                m_fRotation;
    bool                                 m_bSpawned;
    CElement*                            m_pTargetedEntity;
    std::uint8_t                        m_ucFightingStyle;
    int                                  m_iMoveAnim;
    float                                m_fGravity;
    CVector                              m_vecVelocity;
    bool                                 m_bDoingGangDriveby;
    bool                                 m_bHeadless;
    bool                                 m_bFrozen;
    bool                                 m_bStealthAiming;
    CVehicle*                            m_pJackingVehicle;

    CVehicle*    m_pVehicle;
    std::uint32_t m_uiVehicleSeat;
    std::uint32_t m_uiVehicleAction;

    bool m_bSyncable;
    bool m_bCollisionsEnabled;

    std::int64_t             m_llLastFarSyncTick = 0;
    std::vector<CPlayer*> m_nearPlayersList;

private:
    CPedManager* m_pPedManager;
};
