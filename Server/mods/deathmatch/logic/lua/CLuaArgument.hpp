/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/lua/ILuaArgument.h
 *  PURPOSE:     Lua argument handler class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include <string>

extern "C"
{
    #include "lua.h"
}
#include "../common/CBitStream.h"
#include "json.h"

class CElement;
class ILuaArgument;

#define LUA_TTABLEREF 9
#define LUA_TSTRING_LONG 10

class ILuaArgument
{
public:
    virtual ~ILuaArgument() noexcept = 0;

    virtual const ILuaArgument& operator=(const ILuaArgument& Argument) noexcept = 0;

    virtual bool operator==(const ILuaArgument& Argument) const noexcept = 0;
    virtual bool operator!=(const ILuaArgument& Argument) const noexcept = 0;

    virtual void Read(lua_State* luaVM, int iArgument, CFastHashMap<const void*, ILuaArgument*>* pKnownTables = nullptr) noexcept = 0;

    virtual void Push(
        lua_State* luaVM,
        CFastHashMap<ILuaArgument*, int>* pKnownTables = nullptr
    ) const noexcept = 0;

    virtual void ReadBool(bool bBool) noexcept = 0;
    virtual void ReadNumber(double dNumber) noexcept = 0;
    virtual void ReadString(const std::string& strString) noexcept = 0;
    virtual void ReadElement(CElement* pElement) noexcept = 0;
    virtual void ReadElementID(ElementID ID) noexcept = 0;
    virtual void ReadScriptID(std::uint32_t uiScriptID) noexcept = 0;
    virtual void ReadTable(ILuaArgument* table) noexcept = 0;

    constexpr int GetType() const noexcept { return m_iType; }

    constexpr bool               GetBoolean() const noexcept { return m_bBoolean; }
    constexpr lua_Number         GetNumber() const noexcept { return m_Number; }
    constexpr const std::string& GetString() const noexcept { return m_strString; }
    constexpr void*              GetUserData() const noexcept { return m_pUserData; }
    virtual CElement*          GetElement() const noexcept = 0;
    virtual bool               GetAsString(SString& strBuffer) noexcept = 0;

    virtual bool         ReadFromBitStream(NetBitStreamInterface& bitStream, std::vector<ILuaArgument*>* pKnownTables = nullptr) noexcept = 0;
    virtual bool         WriteToBitStream(NetBitStreamInterface& bitStream, CFastHashMap<ILuaArgument*, std::uint32_t>* pKnownTables = nullptr) const noexcept = 0;
    virtual json_object* WriteToJSONObject(bool bSerialize = false, CFastHashMap<ILuaArgument*, std::uint32_t>* pKnownTables = nullptr) noexcept = 0;
    virtual bool         ReadFromJSONObject(json_object* object, std::vector<ILuaArgument*>* pKnownTables = nullptr) noexcept = 0;
    virtual char*        WriteToString(char* szBuffer, int length) noexcept = 0;

    virtual bool IsEqualTo(const ILuaArgument& compareTo, std::set<const ILuaArgument*>* knownTables = nullptr) const noexcept = 0;
protected:
    virtual void LogUnableToPacketize(const char* szMessage) const noexcept = 0;

    int           m_iType;
    bool          m_bBoolean;
    lua_Number    m_Number;
    std::string   m_strString;
    void*         m_pUserData;
    ILuaArgument* m_pTableData;
    bool          m_bWeakTableRef;

#ifdef MTA_DEBUG
    std::string m_strFilename;
    int         m_iLine;
#endif

    virtual void CopyRecursive(const ILuaArgument& Argument, CFastHashMap<ILuaArgument*, ILuaArgument*>* pKnownTables = nullptr) noexcept = 0;
    virtual void DeleteTableData() noexcept = 0;
};
