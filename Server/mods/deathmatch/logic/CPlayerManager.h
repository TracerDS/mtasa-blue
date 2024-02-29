/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CPlayerManager.h
 *  PURPOSE:     Player ped entity manager class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

class CPlayerManager;

#pragma once

#include "CCommon.h"
#include "packets/CPacket.h"
#include "CPlayer.h"
#include "../Config.h"

class CPlayerManager
{
    friend class CPlayer;

public:
    CPlayerManager();
    ~CPlayerManager();

    void DoPulse();
    void PulseZombieCheck();

    void SetScriptDebugging(class CScriptDebugging* pScriptDebugging) noexcept {
        m_pScriptDebugging = pScriptDebugging;
    }

    CPlayer* Create(const NetServerPlayerID& PlayerSocket);
    void     DeleteAll();

    std::uint32_t Count() const noexcept { return m_Players.size(); }
    std::uint32_t CountJoined();
    bool          Exists(CPlayer* pPlayer);

    CPlayer* Get(const NetServerPlayerID& PlayerSocket);
    CPlayer* Get(const char* szNick, bool bCaseSensitive = false);

    std::list<CPlayer*>::const_iterator IterBegin() { return m_Players.begin(); };
    std::list<CPlayer*>::const_iterator IterEnd() { return m_Players.end(); };

    std::size_t BroadcastOnlyJoined(const CPacket& Packet, CPlayer* pSkip = nullptr);
    std::size_t BroadcastDimensionOnlyJoined(const CPacket& Packet, std::uint16_t usDimension, CPlayer* pSkip = nullptr);
    std::size_t BroadcastOnlySubscribed(const CPacket& Packet, CElement* pElement, const char* szName, CPlayer* pSkip = nullptr);

    static void Broadcast(const CPacket& Packet, const std::set<CPlayer*>& sendList);
    static void Broadcast(const CPacket& Packet, const std::list<CPlayer*>& sendList);
    static void Broadcast(const CPacket& Packet, const std::vector<CPlayer*>& sendList);
    static void Broadcast(const CPacket& Packet, const std::multimap<std::uint16_t, CPlayer*>& groupMap);

    static bool IsValidPlayerModel(std::uint16_t model);

    void ClearElementData(CElement* pElement, const std::string& name);
    void ClearElementData(CElement* pElement);

    void               ResetAll();
    void               OnPlayerJoin(CPlayer* pPlayer);
    const CMtaVersion& GetLowestConnectedPlayerVersion() const noexcept { return m_strLowestConnectedPlayerVersion; }

private:
    void AddToList(CPlayer* pPlayer);
    void RemoveFromList(CPlayer* pPlayer);

    class CScriptDebugging* m_pScriptDebugging;

    CMappedList<CPlayer*>                 m_Players;
    std::map<NetServerPlayerID, CPlayer*> m_SocketPlayerMap;
    CMtaVersion                           m_strLowestConnectedPlayerVersion;
    CElapsedTime                          m_ZombieCheckTimer;
};
