/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CPerfStatModule.h
 *  PURPOSE:
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CBandwidthSettings.h"

class CLuaMain;
class CRegistry;
struct lua_State;

//
// Use global struct instead of calls for efficient gathering of certain stats
//
struct SStatData
{
    ZERO_ON_NEW

    struct
    {
        SFixedArray<long long, ZONE_MAX> llSentPacketsByZone;
        SFixedArray<long long, ZONE_MAX> llSentBytesByZone;
        SFixedArray<long long, ZONE_MAX> llSkippedPacketsByZone;
        SFixedArray<long long, ZONE_MAX> llSkippedBytesByZone;
    } puresync;

    struct
    {
        long long llSyncPacketsSkipped;
        long long llSyncBytesSkipped;
        long long llLightSyncPacketsSent;
        long long llLightSyncBytesSent;
    } lightsync;

    bool bFunctionTimingActive;
    int  iDbJobDataCount;
    int  iDbConnectionCount;
};

extern std::unique_ptr<SStatData> g_pStats;

//
// CPerfStatResult
//
// Result of GetStats
//
class CPerfStatResult
{
    std::vector<SString> colNames;
    std::vector<SString> cellList;
    int                  iNumColumns;
    int                  iNumRows;

public:
    CPerfStatResult()
    {
        iNumColumns = 0;
        iNumRows = 0;
    }

    const SString& ColumnName(std::uint32_t c) const
    {
        std::uint32_t idx = c;
        if (idx < colNames.size())
            return colNames[idx];
        static SString dummy;
        return dummy;
    }

    int ColumnCount() const noexcept { return iNumColumns; }

    int RowCount() const noexcept { return iNumRows; }

    void AddColumn(const SString& strColumnName) noexcept 
    {
        colNames.push_back(strColumnName);
        iNumColumns++;
    }

    SString* AddRow() noexcept 
    {
        iNumRows++;
        cellList.insert(cellList.end(), ColumnCount(), SString());
        return &cellList[cellList.size() - ColumnCount()];
    }

    SString& Data(std::uint32_t c, std::uint32_t r) noexcept 
    {
        std::uint32_t idx = c + r * ColumnCount();
        if (idx < cellList.size())
            return cellList[idx];
        static SString cellDummy;
        return cellDummy;
    }

    void Clear() noexcept 
    {
        colNames.clear();
        cellList.clear();
        iNumColumns = 0;
        iNumRows = 0;
    }
};

//
// CPerfStatModule
//
class CPerfStatModule
{
public:
    virtual ~CPerfStatModule() noexcept {}

    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;
    virtual void           Stop() noexcept {};
};

//
// CPerfStatLuaTiming
//
class CPerfStatLuaTiming : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatLuaTiming
    virtual void OnLuaMainCreate(CLuaMain* pLuaMain) = 0;
    virtual void OnLuaMainDestroy(CLuaMain* pLuaMain) = 0;
    virtual void UpdateLuaTiming(CLuaMain* pLuaMain, const char* szEventName, TIMEUS timeUs) = 0;

    static CPerfStatLuaTiming* GetSingleton();
};

//
// CPerfStatLuaMemory
//
class CPerfStatLuaMemory : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatLuaMemory
    virtual void OnLuaMainCreate(CLuaMain* pLuaMain) = 0;
    virtual void OnLuaMainDestroy(CLuaMain* pLuaMain) = 0;

    static CPerfStatLuaMemory* GetSingleton();
};

//
// CPerfStatLibMemory
//
class CPerfStatLibMemory : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatLibMemory

    static CPerfStatLibMemory* GetSingleton();
};

//
// CPerfStatPacketUsage
//
class CPerfStatPacketUsage : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatPacketUsage

    static CPerfStatPacketUsage* GetSingleton();
};

//
// CPerfStatRPCPacketUsage
//
class CPerfStatRPCPacketUsage : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatRPCPacketUsage
    virtual void UpdatePacketUsageIn(std::uint8_t ucRpcId, std::uint32_t uiSize) = 0;
    virtual void UpdatePacketUsageOut(std::uint8_t ucRpcId, std::uint32_t uiSize) = 0;

    static CPerfStatRPCPacketUsage* GetSingleton();
};

//
// CPerfStatEventPacketUsage
//
class CPerfStatEventPacketUsage : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatRPCPacketUsage
    virtual void UpdateElementDataUsageOut(const char* szName, std::uint32_t uiNumPlayers, std::uint32_t uiSize) = 0;
    virtual void UpdateElementDataUsageRelayed(const char* szName, std::uint32_t uiNumPlayers, std::uint32_t uiSize) = 0;
    virtual void UpdateEventUsageOut(const char* szName, std::uint32_t uiNumPlayers) = 0;

    static CPerfStatEventPacketUsage* GetSingleton();
};

//
// CPerfStatPlayerPacketUsage
//
class CPerfStatPlayerPacketUsage : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    static CPerfStatPlayerPacketUsage* GetSingleton();
};

//
// CPerfStatBandwidthUsage
//
class CPerfStatBandwidthUsage : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;
    virtual void           Stop() = 0;

    // CPerfStatBandwidthUsage

    static CPerfStatBandwidthUsage* GetSingleton();
};

//
// CPerfStatSqliteTiming
//
class CPerfStatSqliteTiming : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatSqliteTiming
    virtual void OnSqliteOpen(CRegistry* pRegistry, const SString& strFileName) = 0;
    virtual void OnSqliteClose(CRegistry* pRegistry) = 0;
    virtual void UpdateSqliteTiming(CRegistry* pRegistry, const char* szQuery, TIMEUS timeUs) = 0;
    virtual void SetCurrentResource(lua_State* luaVM) = 0;

    static CPerfStatSqliteTiming* GetSingleton();
};

//
// CPerfStatBandwidthReduction
//
class CPerfStatBandwidthReduction : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatBandwidthReduction

    static CPerfStatBandwidthReduction* GetSingleton();
};

//
// CPerfStatServerInfo
//
class CPerfStatServerInfo : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatServerInfo

    static CPerfStatServerInfo* GetSingleton();
};

//
// CPerfStatServerTiming
//
class CPerfStatServerTiming : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    static CPerfStatServerTiming* GetSingleton();
};

//
// CPerfStatFunctionTiming
//
class CPerfStatFunctionTiming : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatFunctionTiming
    virtual void UpdateTiming(const SString& strResourceName, const char* szFunctionName, TIMEUS timeUs, std::uint32_t uiDeltaBytes) = 0;

    static CPerfStatFunctionTiming* GetSingleton();
    static TIMEUS                   ms_PeakUsThresh;
};

//
// CPerfStatDebugInfo
//
class CPerfStatDebugInfo : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatDebugInfo
    virtual bool IsActive(const char* szSectionName = NULL) = 0;
    virtual void AddLine(const SString& strSection, const SString& strData) = 0;

    static CPerfStatDebugInfo* GetSingleton();
};

//
// CPerfStatDebugTable
//
class CPerfStatDebugTable : public CPerfStatModule
{
public:
    // CPerfStatModule
    virtual const SString& GetCategoryName() = 0;
    virtual void           DoPulse() = 0;
    virtual void           GetStats(CPerfStatResult* pOutResult, const std::map<SString, int>& optionMap, const SString& strFilter) = 0;

    // CPerfStatDebugInfo
    virtual void RemoveLines(const SString& strKeyMatch) = 0;
    virtual void UpdateLine(const SString& strKey, int iLifeTimeMs, ...) = 0;

    static CPerfStatDebugTable* GetSingleton();
};
