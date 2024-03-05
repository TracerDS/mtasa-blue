/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/lua/CLuaArgument.h
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
class CLuaArguments;

#define LUA_TTABLEREF 9
#define LUA_TSTRING_LONG 10

class CLuaArgument
{
public:
    CLuaArgument();
    CLuaArgument(const CLuaArgument& Argument, CFastHashMap<CLuaArguments*, CLuaArguments*>* pKnownTables = nullptr);
    CLuaArgument(lua_State* luaVM, int iArgument, CFastHashMap<const void*, CLuaArguments*>* pKnownTables = nullptr);
    ~CLuaArgument();

    const CLuaArgument& operator=(const CLuaArgument& Argument);
    bool                operator==(const CLuaArgument& Argument) const;
    bool                operator!=(const CLuaArgument& Argument) const;

    void Read(lua_State* luaVM, int iArgument, CFastHashMap<const void*, CLuaArguments*>* pKnownTables = nullptr);
    void Push(lua_State* luaVM, CFastHashMap<CLuaArguments*, int>* pKnownTables = nullptr) const;

    void ReadBool(bool bBool);
    void ReadNumber(double dNumber);
    void ReadString(const std::string& strString);
    void ReadElement(CElement* pElement);
    void ReadElementID(ElementID ID);
    void ReadScriptID(std::uint32_t uiScriptID);
    void ReadTable(class CLuaArguments* table);

    int GetType() const noexcept { return m_iType; };

    bool               GetBoolean() const noexcept { return m_bBoolean; };
    lua_Number         GetNumber() const noexcept { return m_Number; };
    const std::string& GetString() const noexcept { return m_strString; };
    void*              GetUserData() const noexcept { return m_pUserData; };
    CElement*          GetElement() const noexcept;
    bool               GetAsString(SString& strBuffer) const noexcept;

    bool         ReadFromBitStream(NetBitStreamInterface& bitStream, std::vector<CLuaArguments*>* pKnownTables = nullptr);
    bool         WriteToBitStream(NetBitStreamInterface& bitStream, CFastHashMap<CLuaArguments*, std::uint32_t>* pKnownTables = nullptr) const;
    json_object* WriteToJSONObject(bool bSerialize = false, CFastHashMap<CLuaArguments*, std::uint32_t>* pKnownTables = nullptr);
    bool         ReadFromJSONObject(json_object* object, std::vector<CLuaArguments*>* pKnownTables = nullptr);
    char*        WriteToString(char* szBuffer, int length);

    bool IsEqualTo(const CLuaArgument& compareTo, std::set<const CLuaArguments*>* knownTables = nullptr) const;

private:
    void LogUnableToPacketize(const char* szMessage) const;

    int            m_iType;
    bool           m_bBoolean;
    lua_Number     m_Number;
    std::string    m_strString;
    void*          m_pUserData;
    CLuaArguments* m_pTableData;
    bool           m_bWeakTableRef;

#ifdef MTA_DEBUG
    std::string m_strFilename;
    int         m_iLine;
#endif

    void CopyRecursive(const CLuaArgument& Argument, CFastHashMap<CLuaArguments*, CLuaArguments*>* pKnownTables = nullptr);
    void DeleteTableData();
};
