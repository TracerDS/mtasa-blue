/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CBanManager.h
 *  PURPOSE:     Ban manager class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CClient.h"
#include "CPlayerManager.h"

class CBanManager
{
public:
    CBanManager();
    virtual ~CBanManager();

    void DoPulse();

    CBan* AddBan(CPlayer* pPlayer, const SString& strBanner = "Console", const SString& strReason = "", time_t tTimeOfUnban = 0);
    CBan* AddBan(const SString& strIP, const SString& strBanner = "Console", const SString& strReason = "", time_t tTimeOfUnban = 0);

    CBan* AddSerialBan(CPlayer* pPlayer, CClient* pBanner = nullptr, const SString& strReason = "", time_t tTimeOfUnban = 0);
    CBan* AddSerialBan(const SString& strSerial, CClient* pBanner = nullptr, const SString& strReason = "", time_t tTimeOfUnban = 0);

    CBan* AddAccountBan(CPlayer* pPlayer, CClient* pBanner = nullptr, const SString& strReason = "", time_t tTimeOfUnban = 0);
    CBan* AddAccountBan(const SString& szAccount, CClient* pBanner = nullptr, const SString& strReason = "", time_t tTimeOfUnban = 0);

    CBan* AddBan(const SString& strBanner = "Console", const SString& strReason = "", time_t tTimeOfUnban = 0);

    CBan* GetBanFromScriptID(std::uint32_t uiScriptID);

    bool  IsSpecificallyBanned(const char* szIP);
    bool  IsSerialBanned(const char* szSerial);
    bool  IsAccountBanned(const char* szAccount);
    CBan* GetBanFromAccount(const char* szAccount);
    void  RemoveBan(CBan* pBan);

    CBan* GetBanFromSerial(const char* szSerial);
    CBan* GetBanFromIP(const char* szIP);

    std::uint32_t GetBansWithNick(const char* szNick);
    std::uint32_t GetBansWithBanner(const char* szBanner);

    bool        LoadBanList();
    bool        ReloadBanList();
    void        SaveBanList();
    void        SafeSetValue(CXMLNode* pNode, const char* szKey, const std::string& strValue);
    void        SafeSetValue(CXMLNode* pNode, const char* szKey, std::uint32_t);
    std::string SafeGetValue(CXMLNode* pNode, const char* szKey);
    bool        IsValidIP(const char* szIP);
    static void SetBansModified() noexcept { ms_bSaveRequired = true; }

    CMappedList<CBan*>& GetBans() noexcept { return m_BanManager; }
    const CMappedList<CBan*>& GetBans() const noexcept { return m_BanManager; }

    list<CBan*>::const_iterator IterBegin() { return m_BanManager.begin(); };
    list<CBan*>::const_iterator IterEnd() { return m_BanManager.end(); };

private:
    SString m_strPath;

    CMappedList<CBan*> m_BanManager;
    std::set<CBan*>    m_BansBeingDeleted;

    time_t m_tUpdate;

    bool        IsValidIPPart(const char* szIP);
    bool        m_bAllowSave;
    static bool ms_bSaveRequired;
};
