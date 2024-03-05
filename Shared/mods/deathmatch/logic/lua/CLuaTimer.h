/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/lua/CLuaTimer.h
 *  PURPOSE:     Lua timer class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

class CLuaTimer;

#pragma once

// Define includes
#include "lua/LuaCommon.h"
#include "lua/CLuaArguments.h"

#define LUA_TIMER_MIN_INTERVAL      0

class CLuaTimer
{
public:
    CLuaTimer(const CLuaFunctionRef& iLuaFunction, const CLuaArguments& Arguments) noexcept;
    ~CLuaTimer() noexcept;

    void RemoveScriptID();

    CTickCount GetStartTime() const noexcept { return m_llStartTime; };
    void       SetStartTime(CTickCount llStartTime) noexcept { m_llStartTime = llStartTime; };

    CTickCount GetDelay() const noexcept { return m_llDelay; };
    void       SetDelay(CTickCount llDelay) noexcept { m_llDelay = llDelay; };

    std::uint32_t GetRepeats() const noexcept { return m_uiRepeats; };
    void          SetRepeats(std::uint32_t uiRepeats) noexcept { m_uiRepeats = uiRepeats; }

    void ExecuteTimer(class CLuaMain* pLuaMain);

    CTickCount GetTimeLeft();

    std::uint32_t        GetScriptID() const noexcept { return m_uiScriptID; }
    const SLuaDebugInfo& GetLuaDebugInfo() const noexcept { return m_LuaDebugInfo; }
    void                 SetLuaDebugInfo(const SLuaDebugInfo& luaDebugInfo) { m_LuaDebugInfo = luaDebugInfo; }

private:
    CLuaFunctionRef m_iLuaFunction;
    CLuaArguments   m_Arguments;
    CTickCount      m_llStartTime;
    CTickCount      m_llDelay;
    std::uint32_t   m_uiRepeats;
    std::uint32_t   m_uiScriptID;
    SLuaDebugInfo   m_LuaDebugInfo;
};
