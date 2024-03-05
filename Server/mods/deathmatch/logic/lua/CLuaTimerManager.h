/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/lua/CLuaTimerManager.h
 *  PURPOSE:     Lua timer manager class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

class CLuaTimerManager;

#pragma once

#include "LuaCommon.h"
#include "lua/CLuaTimer.h"
#include <list>

class CLuaTimerManager
{
public:
    CLuaTimerManager() noexcept {}
    ~CLuaTimerManager() noexcept { RemoveAllTimers(); };

    void DoPulse(CLuaMain* pLuaMain);

    CLuaTimer* GetTimerFromScriptID(std::uint32_t uiScriptID);

    CLuaTimer*  AddTimer(const CLuaFunctionRef& iLuaFunction, CTickCount llTimeDelay, std::uint32_t uiRepeats, const CLuaArguments& Arguments);
    void        RemoveTimer(CLuaTimer* pLuaTimer);
    void        RemoveAllTimers();
    std::size_t GetTimerCount() const noexcept { return m_TimerList.size(); }

    void ResetTimer(CLuaTimer* pLuaTimer);

    CFastList<CLuaTimer*>& GetTimers() noexcept { return m_TimerList; }
    const CFastList<CLuaTimer*>& GetTimers() const noexcept { return m_TimerList; }

    CFastList<CLuaTimer*>::const_iterator IterBegin() { return m_TimerList.begin(); }
    CFastList<CLuaTimer*>::const_iterator IterEnd() { return m_TimerList.end(); }

private:
    CFastList<CLuaTimer*>  m_TimerList;
    std::deque<CLuaTimer*> m_ProcessQueue;
    CLuaTimer*             m_pPendingDelete = nullptr;
    CLuaTimer*             m_pProcessingTimer = nullptr;
};
