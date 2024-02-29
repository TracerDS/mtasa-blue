/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/lua/CLuaArguments.h
 *  PURPOSE:     Lua argument manager class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

extern "C"
{
    #include "lua.h"
}

#include <vector>

#include "../common/CBitStream.h"
#include "json.h"
#include "CLuaFunctionRef.h"
#include "CLuaArguments.hpp"

inline void LUA_CHECKSTACK(lua_State* L, int size)
{
    if (lua_getstackgap(L) < size + 5)
        lua_checkstack(L, (size + 2) * 3 + 4);
}

class CAccessControlList;
class CAccessControlListGroup;
class CAccount;
class CBan;
class CElement;
class CLuaTimer;
class CResource;
class CTextDisplay;
class CTextItem;
class CDbJobData;

class CLuaArguments //: public ILuaArguments
{
public:
    CLuaArguments() noexcept {}
    CLuaArguments(const CLuaArguments& Arguments, CFastHashMap<CLuaArguments*, CLuaArguments*>* pKnownTables = nullptr) noexcept;

    void CopyRecursive(const CLuaArguments& Arguments, CFastHashMap<CLuaArguments*, CLuaArguments*>* pKnownTables = nullptr) noexcept ;

    const CLuaArguments& operator=(const CLuaArguments& Arguments) noexcept;
    CLuaArgument*        operator[](const std::uint32_t uiPosition) const noexcept;

    void ReadArgument(lua_State* luaVM, std::int32_t uiIndex) noexcept ;
    void ReadArguments(lua_State* luaVM, std::int32_t uiIndexBegin = 1) noexcept ;
    void PushArguments(lua_State* luaVM) const noexcept ;
    void PushArguments(const CLuaArguments& Arguments) noexcept ;
    bool Call(class CLuaMain* pLuaMain, const CLuaFunctionRef& iLuaFunction, CLuaArguments* returnValues = nullptr) const noexcept ;
    bool CallGlobal(class CLuaMain* pLuaMain, const char* szFunction, CLuaArguments* returnValues = nullptr) const noexcept ;

    void ReadTable(lua_State* luaVM, int iIndexBegin, CFastHashMap<const void*, CLuaArguments*>* pKnownTables = nullptr) noexcept ;
    void PushAsTable(lua_State* luaVM, CFastHashMap<CLuaArguments*, int>* pKnownTables = nullptr) const noexcept ;

    CLuaArgument* PushNil() noexcept ;
    CLuaArgument* PushBoolean(bool bBool) noexcept ;
    CLuaArgument* PushNumber(double dNumber) noexcept ;
    CLuaArgument* PushString(const std::string& strString) noexcept ;
    CLuaArgument* PushElement(CElement* pElement) noexcept ;
    CLuaArgument* PushBan(CBan* pBan) noexcept ;
    CLuaArgument* PushACL(CAccessControlList* pACL) noexcept ;
    CLuaArgument* PushACLGroup(CAccessControlListGroup* pACLGroup) noexcept ;
    CLuaArgument* PushAccount(CAccount* pAccount) noexcept ;
    CLuaArgument* PushResource(CResource* pResource) noexcept ;
    CLuaArgument* PushTextDisplay(CTextDisplay* pTextDisplay) noexcept ;
    CLuaArgument* PushTextItem(CTextItem* pTextItem) noexcept ;
    CLuaArgument* PushTimer(CLuaTimer* pLuaTimer) noexcept ;
    CLuaArgument* PushDbQuery(CDbJobData* pJobData) noexcept ;

    CLuaArgument* PushArgument(const CLuaArgument& argument) noexcept ;
    CLuaArgument* PushTable(CLuaArguments* table) noexcept ;

    void DeleteArguments() noexcept ;
    void ValidateTableKeys() noexcept ;
    void Pop() noexcept ;

    bool         ReadFromBitStream(NetBitStreamInterface& bitStream, std::vector<CLuaArguments*>* pKnownTables = nullptr) noexcept ;
    bool         ReadFromJSONString(const char* szJSON) noexcept ;
    bool         WriteToBitStream(NetBitStreamInterface& bitStream, CFastHashMap<CLuaArguments*, std::uint32_t>* pKnownTables = nullptr) const noexcept ;
    bool         WriteToJSONString(std::string& strJSON, bool bSerialize = false, int flags = JSON_C_TO_STRING_PLAIN) noexcept ;
    json_object* WriteTableToJSONObject(bool bSerialize = false, CFastHashMap<CLuaArguments*, std::uint32_t>* pKnownTables = nullptr) noexcept ;
    json_object* WriteToJSONArray(bool bSerialize) noexcept ;
    bool         ReadFromJSONObject(json_object* object, std::vector<CLuaArguments*>* pKnownTables = nullptr) noexcept ;
    bool         ReadFromJSONArray(json_object* object, std::vector<CLuaArguments*>* pKnownTables = nullptr) noexcept ;

    bool IsEqualTo(const CLuaArguments& compareTo, std::set<const CLuaArguments*>* knownTables = nullptr) const noexcept ;

    constexpr std::size_t Count() const noexcept { return m_Arguments.size(); }

private:
    std::vector<CLuaArgument*> m_Arguments;
};
