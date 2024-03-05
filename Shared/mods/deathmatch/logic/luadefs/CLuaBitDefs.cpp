/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        Shared/mods/deathmatch/logic/luadefs/CLuaBitDefs.h
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#include "StdInc.h"
#include "CLuaBitDefs.h"
#include "CScriptArgReader.h"

#define mask(n) ((1 << (n)) - 1)

void CLuaBitDefs::LoadFunctions()
{
    constexpr static const std::pair<const char*, lua_CFunction> functions[]{
        {"bitAnd", bitAnd},         {"bitNot", bitNot},         {"bitOr", bitOr},         {"bitTest", bitTest},     {"bitXor", bitXor},

        {"bitLRotate", bitLRotate}, {"bitRRotate", bitRRotate}, {"bitLShift", bitLShift}, {"bitRShift", bitRShift}, {"bitArShift", bitArShift},

        {"bitExtract", bitExtract}, {"bitReplace", bitReplace},
    };

    // Add functions
    for (const auto& [name, func] : functions)
        CLuaCFunctions::AddFunction(name, func);
}

int CLuaBitDefs::bitAnd(lua_State* luaVM)
{
    //  std::uint32_t bitAnd ( std::uint32_t var1, std::uint32_t var2, ... )
    std::uint32_t uiVar1;
    std::uint32_t uiVar2;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar1, false);
    argStream.ReadNumber(uiVar2, false);

    if (!argStream.HasErrors())
    {
        std::uint32_t uiResult = uiVar1 & uiVar2;
        while (argStream.NextIsNumber())
        {
            std::uint32_t uiVar;
            argStream.ReadNumber(uiVar, false);

            uiResult &= uiVar;
        }

        lua_pushnumber(luaVM, uiResult);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaBitDefs::bitNot(lua_State* luaVM)
{
    //  std::uint32_t bitNot ( std::uint32_t var )
    std::uint32_t uiVar;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar, false);

    if (!argStream.HasErrors())
    {
        lua_pushnumber(luaVM, ~uiVar);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaBitDefs::bitOr(lua_State* luaVM)
{
    //  std::uint32_t bitOr ( std::uint32_t var1, std::uint32_t var2, ... )
    std::uint32_t uiVar1;
    std::uint32_t uiVar2;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar1, false);
    argStream.ReadNumber(uiVar2, false);

    if (!argStream.HasErrors())
    {
        std::uint32_t uiResult = uiVar1 | uiVar2;
        while (argStream.NextIsNumber())
        {
            std::uint32_t uiVar;
            argStream.ReadNumber(uiVar, false);

            uiResult |= uiVar;
        }

        lua_pushnumber(luaVM, uiResult);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaBitDefs::bitTest(lua_State* luaVM)
{
    //  std::uint32_t bitTest ( std::uint32_t var1, std::uint32_t var2, ... )
    std::uint32_t uiVar1;
    std::uint32_t uiVar2;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar1, false);
    argStream.ReadNumber(uiVar2, false);

    if (!argStream.HasErrors())
    {
        std::uint32_t uiResult = uiVar1 & uiVar2;
        while (argStream.NextIsNumber())
        {
            std::uint32_t uiVar;
            argStream.ReadNumber(uiVar, false);

            uiResult &= uiVar;
        }

        bool bTested = uiResult != 0;
        lua_pushboolean(luaVM, bTested);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushnil(luaVM);
    return 1;
}

int CLuaBitDefs::bitXor(lua_State* luaVM)
{
    //  std::uint32_t bitXor ( std::uint32_t var1, std::uint32_t var2 )
    std::uint32_t uiVar1;
    std::uint32_t uiVar2;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar1, false);
    argStream.ReadNumber(uiVar2, false);

    if (!argStream.HasErrors())
    {
        std::uint32_t uiResult = uiVar1 ^ uiVar2;
        while (argStream.NextIsNumber())
        {
            std::uint32_t uiVar;
            argStream.ReadNumber(uiVar, false);

            uiResult ^= uiVar;
        }

        lua_pushnumber(luaVM, uiResult);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaBitDefs::bitLRotate(lua_State* luaVM)
{
    //  std::uint32_t bitLRotate ( std::uint32_t var, int disp )
    std::uint32_t uiVar;
    int  iDisp;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar, false);
    argStream.ReadNumber(iDisp);

    if (!argStream.HasErrors())
    {
        iDisp &= (32 - 1);            // iDisp %= 32
        std::uint32_t uiResult = (uiVar << iDisp) | (uiVar >> (32 - iDisp));

        lua_pushnumber(luaVM, uiResult);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaBitDefs::bitRRotate(lua_State* luaVM)
{
    //  std::uint32_t bitRRotate ( std::uint32_t var, int disp )
    std::uint32_t uiVar;
    int  iDisp;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar, false);
    argStream.ReadNumber(iDisp);

    if (!argStream.HasErrors())
    {
        iDisp &= (32 - 1);            // iDisp %= 32
        std::uint32_t uiResult = (uiVar >> iDisp) | (uiVar << (32 - iDisp));

        lua_pushnumber(luaVM, uiResult);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaBitDefs::bitLShift(lua_State* luaVM)
{
    //  std::uint32_t bitLShift ( std::uint32_t var, int disp )
    std::uint32_t uiVar;
    int  iDisp;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar, false);
    argStream.ReadNumber(iDisp);

    if (!argStream.HasErrors())
    {
        std::uint32_t uiResult;

        if (iDisp >= 32)
            uiResult = 0;
        else
            uiResult = uiVar << iDisp;

        lua_pushnumber(luaVM, uiResult);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaBitDefs::bitRShift(lua_State* luaVM)
{
    //  std::uint32_t bitRShift ( std::uint32_t var, int disp )
    std::uint32_t uiVar;
    int  iDisp;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar, false);
    argStream.ReadNumber(iDisp);

    if (!argStream.HasErrors())
    {
        std::uint32_t uiResult;

        if (iDisp >= 32)
            uiResult = 0;
        else
            uiResult = uiVar >> iDisp;

        lua_pushnumber(luaVM, uiResult);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaBitDefs::bitArShift(lua_State* luaVM)
{
    //  std::uint32_t bitArShift ( std::uint32_t var, int disp )
    std::uint32_t uiVar;
    int  iDisp;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar, false);
    argStream.ReadNumber(iDisp);

    if (!argStream.HasErrors())
    {
        std::uint32_t uiResult;

        if (iDisp < 0 || !(uiVar & ((std::uint32_t)1 << (32 - 1))))
        {
            if (iDisp <= -32 || iDisp >= 32)
                uiResult = 0;
            else
            {
                if (iDisp < 0)
                    uiResult = uiVar << -iDisp;
                else
                    uiResult = uiVar >> iDisp;
            }

            lua_pushnumber(luaVM, uiResult);
            return 1;
        }

        if (iDisp >= 32)
            uiResult = 0xFFFFFFFF;
        else
            uiResult = (uiVar >> iDisp) | ~(~(std::uint32_t)0 >> iDisp);

        lua_pushnumber(luaVM, uiResult);
        return 1;
    }
    else
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaBitDefs::bitExtract(lua_State* luaVM)
{
    //  std::uint32_t bitExtract ( std::uint32_t var, int field, int width = 1 )
    std::uint32_t uiVar;
    int  iField;
    int  iWidth;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar, false);
    argStream.ReadNumber(iField);
    argStream.ReadNumber(iWidth, 1);

    if (!argStream.HasErrors())
    {
        if (iField + iWidth > 32)
            argStream.SetCustomError("Trying to access non-exisistent bits");

        if (iField < 0)
            argStream.SetCustomError("field cannot be negative");

        if (iWidth <= 0)
            argStream.SetCustomError("width must be positive");

        if (!argStream.HasErrors())
        {
            lua_pushnumber(luaVM, (uiVar >> iField) & mask(iWidth));
            return 1;
        }
    }

    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return 1;
}

int CLuaBitDefs::bitReplace(lua_State* luaVM)
{
    //  std::uint32_t bitReplace ( std::uint32_t var, std::uint32_t replaceValue, int field, int width = 1 )
    std::uint32_t uiVar;
    std::uint32_t uiReplaceValue;
    int  iField;
    int  iWidth;

    CScriptArgReader argStream(luaVM);
    argStream.ReadNumber(uiVar, false);
    argStream.ReadNumber(uiReplaceValue, false);
    argStream.ReadNumber(iField);
    argStream.ReadNumber(iWidth, 1);

    if (!argStream.HasErrors())
    {
        if (iField + iWidth > 32)
            argStream.SetCustomError("Trying to access non-exisistent bits");

        if (iField < 0)
            argStream.SetCustomError("field cannot be negative");

        if (iWidth <= 0)
            argStream.SetCustomError("width must be positive");

        if (!argStream.HasErrors())
        {
            int iMask = mask(iWidth);

            // Erase bits outside given width
            uiReplaceValue &= iMask;

            lua_pushnumber(luaVM, (uiVar & ~(iMask << iField)) | (uiReplaceValue << iField));
            return 1;
        }
    }

    if (argStream.HasErrors())
        m_pScriptDebugging->LogCustom(luaVM, argStream.GetFullErrorMessage());

    lua_pushboolean(luaVM, false);
    return false;
}
