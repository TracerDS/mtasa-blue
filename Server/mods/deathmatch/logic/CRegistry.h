/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CRegistry.h
 *  PURPOSE:     SQLite registry abstraction class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "CLogger.h"
#include <list>
#include <vector>
#include <string>
#include <sqlite/sqlite3.h>

typedef CAutoRefedPointer<struct CRegistryResultData> CRegistryResult;

class CRegistry
{
    friend class CRegistryManager;
    CRegistry(const std::string& strFileName);
    ~CRegistry();

public:
    void SuspendBatching(std::uint32_t uiTicks);
    void Load(const std::string& strFileName);
    bool IntegrityCheck();

    void CreateTable(const std::string& strTable, const std::string& strDefinition, bool bSilent = false);
    void DropTable(const std::string& strTable);

    bool Delete(const std::string& strTable, const std::string& strWhere);
    bool Insert(const std::string& strTable, const std::string& strValues, const std::string& strColumns);
    bool Select(const std::string& strColumns, const std::string& strTable, const std::string& strWhere, std::uint32_t uiLimit, CRegistryResult* pResult);
    bool Update(const std::string& strTable, const std::string& strSet, const std::string& strWhere);

    bool Query(const std::string& strQuery, class CLuaArguments* pArgs, CRegistryResult* pResult);
    bool Query(const char* szQuery, ...);
    bool Query(CRegistryResult* pResult, const char* szQuery, ...);

    const SString& GetLastError() const noexcept { return m_strLastErrorMessage; }

protected:
    bool SetLastErrorMessage(const std::string& strLastErrorMessage, const std::string& strQuery);
    bool Exec(const std::string& strQuery);
    bool ExecInternal(const char* szQuery);
    bool Query(CRegistryResult* pResult, const char* szQuery, va_list vl);
    bool QueryInternal(const char* szQuery, CRegistryResult* pResult);
    void BeginAutomaticTransaction();
    void EndAutomaticTransaction();

    sqlite3*  m_db;
    bool      m_bOpened;
    bool      m_bInAutomaticTransaction;
    long long m_llSuspendBatchingEndTime;
    SString   m_strLastErrorMessage;
    SString   m_strLastErrorQuery;
    SString   m_strFileName;

private:
    bool Query(const char* szQuery, CRegistryResult* pResult);            // Not defined to catch incorrect usage
};

struct CRegistryResultCell
{
    constexpr CRegistryResultCell() noexcept {}

    CRegistryResultCell(const CRegistryResultCell& cell) noexcept
    {
        nType = cell.nType;
        nLength = cell.nLength;
        nVal = cell.nVal;
        fVal = cell.fVal;
        if ((nType == SQLITE_BLOB || nType == SQLITE_TEXT) && cell.pVal && nLength > 0)
        {
            pVal = new std::uint8_t[nLength];
            memcpy(pVal, cell.pVal, nLength);
        }
    };
    ~CRegistryResultCell() noexcept
    {
        if (pVal)
            delete[] pVal;
    }

    CRegistryResultCell& operator=(const CRegistryResultCell& cell) noexcept
    {
        if (pVal)
            delete[] pVal;

        nType = cell.nType;
        nLength = cell.nLength;
        nVal = cell.nVal;
        fVal = cell.fVal;
        pVal = nullptr;
        if ((nType == SQLITE_BLOB || nType == SQLITE_TEXT) && cell.pVal && nLength > 0)
        {
            pVal = new std::uint8_t[nLength];
            memcpy(pVal, cell.pVal, nLength);
        }
        return *this;
    }

    template <class T>
    constexpr void GetNumber(T& outValue) const noexcept
    {
        outValue = GetNumber<T>();
    }

    template <class T>
    constexpr T GetNumber() const noexcept
    {
        if (nType == SQLITE_INTEGER)
            return static_cast<T>(nVal);
        if (nType == SQLITE_FLOAT)
            return static_cast<T>(fVal);
        return 0;
    }

    int nType{ SQLITE_NULL }; // Type identifier, SQLITE_*
    int nLength{ 0 };         // Length in bytes if nType == SQLITE_BLOB or SQLITE_TEXT
                              // (includes zero terminator if TEXT)
    std::int64_t  nVal{ 0 };
    float         fVal{ 0 };
    std::uint8_t* pVal{ nullptr };
};

using CRegistryResultRow = std::vector<CRegistryResultCell>;
using CRegistryResultIterator = std::list<CRegistryResultRow>::const_iterator;

struct CRegistryResultData
{
    CRegistryResultData() noexcept {}
    ~CRegistryResultData() { SAFE_DELETE(pNextResult); }

    CRegistryResultData* GetThis() noexcept { return this; }
    const CRegistryResultData* GetThis() const noexcept { return this; }

    CRegistryResultIterator begin() const noexcept { return Data.begin(); }
    CRegistryResultIterator end() const noexcept { return Data.end(); }

    const CRegistryResultIterator cbegin() const noexcept { return Data.cbegin(); }
    const CRegistryResultIterator cend() const noexcept { return Data.cend(); }

    std::vector<SString>          ColNames;
    std::list<CRegistryResultRow> Data;
    int                           nRows{0};
    int                           nColumns{0};
    std::uint32_t                 uiNumAffectedRows{0};
    std::uint64_t                 ullLastInsertId{0};
    CRegistryResultData*          pNextResult{nullptr};
};
