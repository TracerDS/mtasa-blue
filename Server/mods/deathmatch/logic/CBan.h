/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CBan.h
 *  PURPOSE:     Ban descriptor class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CCommon.h"
#include "CBanManager.h"
#include <string>

class CBan
{
public:
    CBan() noexcept;
    ~CBan() noexcept;

    const std::string& GetIP() const noexcept { return m_strIP; }
    void               SetIP(const std::string& strIP) noexcept
    {
        CBanManager::SetBansModified();
        m_strIP = strIP;
    }

    const std::string& GetNick() const noexcept { return m_strNick; }
    void               SetNick(const std::string& strNick) noexcept
    {
        CBanManager::SetBansModified();
        m_strNick = strNick;
    }

    const std::string& GetBanner() const noexcept { return m_strBanner; }
    void               SetBanner(const std::string& strBanner) noexcept
    {
        CBanManager::SetBansModified();
        m_strBanner = strBanner;
    }

    const std::string& GetReason() const noexcept { return m_strReason; }
    void               SetReason(const std::string& strReason) noexcept
    {
        CBanManager::SetBansModified();
        m_strReason = strReason;
    }

    const time_t GetTimeOfBan() const noexcept { return m_tTimeOfBan; }
    void         SetTimeOfBan(time_t tTimeOfBan) noexcept
    {
        CBanManager::SetBansModified();
        m_tTimeOfBan = tTimeOfBan;
    }

    time_t GetTimeOfUnban() const noexcept { return m_tTimeOfUnban; }
    void   SetTimeOfUnban(time_t tTimeOfUnban) noexcept
    {
        CBanManager::SetBansModified();
        m_tTimeOfUnban = tTimeOfUnban;
    }

    const std::string& GetSerial() const noexcept { return m_strSerial; }
    void               SetSerial(const std::string& strSerial) noexcept
    {
        CBanManager::SetBansModified();
        m_strSerial = strSerial;
    }

    const std::string& GetAccount() const noexcept { return m_strAccount; }
    void               SetAccount(const std::string& strAccount) noexcept
    {
        CBanManager::SetBansModified();
        m_strAccount = strAccount;
    }

    time_t        GetBanTimeRemaining();
    SString       GetDurationDesc();
    SString       GetReasonText() const;
    std::uint32_t GetScriptID() const noexcept { return m_uiScriptID; }
    bool          IsBeingDeleted() const noexcept { return m_bBeingDeleted; }
    void          SetBeingDeleted() noexcept { m_bBeingDeleted = true; }

private:
    std::string   m_strIP;
    std::string   m_strNick;
    std::string   m_strBanner;
    std::string   m_strReason;
    std::string   m_strSerial;
    std::string   m_strAccount;
    time_t        m_tTimeOfBan;
    time_t        m_tTimeOfUnban;
    std::uint32_t m_uiScriptID;
    bool          m_bBeingDeleted;
};
