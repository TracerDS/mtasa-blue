/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CTextItem.h
 *  PURPOSE:     Text display item class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include <CVector2D.h>
#include "CTextDisplay.h"
#include <list>

enum eTextPriority
{
    PRIORITY_LOW = 0,
    PRIORITY_MEDIUM,
    PRIORITY_HIGH
};

class CTextItem
{
    friend class CTextDisplay;
    friend class CPlayerTextManager;

public:
    CTextItem(const char* szText, const CVector2D& vecPosition,
        eTextPriority Priority = PRIORITY_LOW, const SColor color = -1, float fScale = 1.0f,
        std::uint8_t ucFormat = 0, std::uint8_t ucShadowAlpha = 0) noexcept;
    CTextItem(const CTextItem& TextItem) noexcept;
    ~CTextItem() noexcept;

    bool operator=(const CTextItem& TextItem) noexcept;

    void           SetText(const char* szText) noexcept;
    const SString& GetText() const noexcept { return m_strText; };

    const CVector2D& GetPosition() const noexcept { return m_vecPosition; };
    void             SetPosition(const CVector2D& vecPosition) noexcept;

    void   SetColor(const SColor color) noexcept;
    SColor GetColor() const noexcept { return m_Color; }

    float GetScale() noexcept { return m_fScale; };
    void  SetScale(float fScale) noexcept;

    std::uint8_t GetFormat() const noexcept{ return m_ucFormat; }
    void         SetFormat(std::uint8_t ucFormat) noexcept { m_ucFormat = ucFormat; }

    void          SetPriority(eTextPriority Priority) noexcept { m_Priority = Priority; };
    eTextPriority GetPriority() const noexcept { return m_Priority; };

    std::uint32_t GetUniqueID() const noexcept { return m_ulUniqueId; };
    bool          IsBeingDeleted() const noexcept { return m_bDeletable; };
    std::uint32_t GetScriptID() const noexcept { return m_uiScriptID; }

private:
    SString       m_strText;
    CVector2D     m_vecPosition;
    SColor        m_Color;
    float         m_fScale;
    std::uint8_t  m_ucFormat;
    std::uint8_t  m_ucShadowAlpha;
    std::uint32_t m_ulUniqueId;
    eTextPriority m_Priority;
    bool          m_bDeletable;
    std::uint32_t m_uiScriptID;

    std::list<CTextDisplay*> m_Observers;

    void AddObserver(CTextDisplay* pObserver);
    void RemoveObserver(CTextDisplay* pObserver) noexcept { m_Observers.remove(pObserver); };
    void NotifyObservers();
};
