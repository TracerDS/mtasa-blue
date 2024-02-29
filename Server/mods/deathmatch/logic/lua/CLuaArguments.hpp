/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/lua/ILuaArguments.h
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
#include "CLuaArgument.hpp"

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

class ILuaArguments
{
public:
    virtual ~ILuaArguments() noexcept { DeleteArguments(); }

    virtual void CopyRecursive(const ILuaArguments& Arguments, CFastHashMap<ILuaArguments*, ILuaArguments*>* pKnownTables = nullptr) noexcept = 0;

    virtual const ILuaArguments& operator=(const ILuaArguments& Arguments) noexcept = 0;
    virtual ILuaArgument*        operator[](const std::uint32_t uiPosition) const noexcept = 0;

    virtual void ReadArgument(lua_State* luaVM, std::int32_t uiIndex) noexcept = 0;
    virtual void ReadArguments(lua_State* luaVM, std::int32_t uiIndexBegin = 1) noexcept = 0;
    virtual void PushArguments(lua_State* luaVM) const noexcept = 0;
    virtual void PushArguments(const ILuaArguments& Arguments) noexcept = 0;
    virtual bool Call(class CLuaMain* pLuaMain, const CLuaFunctionRef& iLuaFunction, ILuaArguments* returnValues = nullptr) const noexcept = 0;
    virtual bool CallGlobal(class CLuaMain* pLuaMain, const char* szFunction, ILuaArguments* returnValues = nullptr) const noexcept = 0;

    virtual void ReadTable(lua_State* luaVM, int iIndexBegin, CFastHashMap<const void*, ILuaArguments*>* pKnownTables = nullptr) noexcept = 0;
    virtual void PushAsTable(lua_State* luaVM, CFastHashMap<ILuaArguments*, int>* pKnownTables = nullptr) const noexcept = 0;

    virtual ILuaArgument* PushNil() noexcept = 0;
    virtual ILuaArgument* PushBoolean(bool bBool) noexcept = 0;
    virtual ILuaArgument* PushNumber(double dNumber) noexcept = 0;
    virtual ILuaArgument* PushString(const std::string& strString) noexcept = 0;
    virtual ILuaArgument* PushElement(CElement* pElement) noexcept = 0;
    virtual ILuaArgument* PushBan(CBan* pBan) noexcept = 0;
    virtual ILuaArgument* PushACL(CAccessControlList* pACL) noexcept = 0;
    virtual ILuaArgument* PushACLGroup(CAccessControlListGroup* pACLGroup) noexcept = 0;
    virtual ILuaArgument* PushAccount(CAccount* pAccount) noexcept = 0;
    virtual ILuaArgument* PushResource(CResource* pResource) noexcept = 0;
    virtual ILuaArgument* PushTextDisplay(CTextDisplay* pTextDisplay) noexcept = 0;
    virtual ILuaArgument* PushTextItem(CTextItem* pTextItem) noexcept = 0;
    virtual ILuaArgument* PushTimer(CLuaTimer* pLuaTimer) noexcept = 0;
    virtual ILuaArgument* PushDbQuery(CDbJobData* pJobData) noexcept = 0;

    virtual ILuaArgument* PushArgument(const ILuaArgument& argument) noexcept = 0;
    virtual ILuaArgument* PushTable(ILuaArguments* table) noexcept = 0;

    virtual void DeleteArguments() noexcept = 0;
    virtual void ValidateTableKeys() noexcept = 0;
    virtual void Pop() noexcept = 0;

    virtual bool         ReadFromBitStream(NetBitStreamInterface& bitStream, std::vector<ILuaArguments*>* pKnownTables = nullptr) noexcept = 0;
    virtual bool         ReadFromJSONString(const char* szJSON) noexcept = 0;
    virtual bool         WriteToBitStream(NetBitStreamInterface& bitStream, CFastHashMap<ILuaArguments*, std::uint32_t>* pKnownTables = nullptr) const noexcept = 0;
    virtual bool         WriteToJSONString(std::string& strJSON, bool bSerialize = false, int flags = JSON_C_TO_STRING_PLAIN) noexcept = 0;
    virtual json_object* WriteTableToJSONObject(bool bSerialize = false, CFastHashMap<ILuaArguments*, std::uint32_t>* pKnownTables = nullptr) noexcept = 0;
    virtual json_object* WriteToJSONArray(bool bSerialize) noexcept = 0;
    virtual bool         ReadFromJSONObject(json_object* object, std::vector<ILuaArguments*>* pKnownTables = nullptr) noexcept = 0;
    virtual bool         ReadFromJSONArray(json_object* object, std::vector<ILuaArguments*>* pKnownTables = nullptr) noexcept = 0;

    constexpr std::size_t Count() const noexcept { return m_Arguments.size(); }

    std::vector<ILuaArgument*>& GetArguments() noexcept { return m_Arguments; }
    const std::vector<ILuaArgument*>& GetArguments() const noexcept { return m_Arguments; }

    virtual bool IsEqualTo(const ILuaArguments& compareTo, std::set<const ILuaArguments*>* knownTables = nullptr) const noexcept;

protected:
    std::vector<ILuaArgument*> m_Arguments;
};
