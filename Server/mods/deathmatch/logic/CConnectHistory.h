/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CConnectHistory.h
 *  PURPOSE:     Client connection history class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include <cstdint>
#include <vector>
#include <SString.h>
#include <SharedUtil.FastHashMap.h>

using HistoryItemMap = CFastHashMap<SString, struct CConnectHistoryItem>;
using JoinTimesMap = std::vector<std::int64_t>;

struct CConnectHistoryItem
{
    std::int64_t llBanEndTime{0};
    JoinTimesMap joinTimes;
};

class CConnectHistory
{
public:
    CConnectHistory(std::uint32_t ulMaxConnections, std::uint32_t ulSamplePeriod, std::uint32_t ulBanLength);

    // Note strIP, can be any string that uniquely identifies the connection
    bool                 AddConnect(const std::string& strIP);
    bool                 IsFlooding(const std::string& strIP);
    CConnectHistoryItem& GetHistoryItem(const std::string& strIP);
    std::uint32_t        GetTotalFloodingCount();
    SString              DebugDump(std::int64_t llTickCountAdd);

private:
    void         RemoveExpired();
    std::int64_t GetModuleTickCount64();

    std::uint32_t m_ulSamplePeriod;
    std::uint32_t m_ulMaxConnections;
    std::uint32_t m_ulBanLength;
    std::int64_t m_llTimeLastRemoveExpired;
    std::int64_t m_llDebugTickCountOffset;
    HistoryItemMap m_HistoryItemMap;
};
