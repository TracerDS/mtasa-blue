/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        SharedUtil.Profiling.h
 *  PURPOSE:     Shared stuff which measures things
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/
#pragma once

#include <string>
#include <map>
#include <vector>
#include "SharedUtil.Time.h"

namespace SharedUtil
{
    //
    // Performance stat gathering
    //

    enum eStatEventType
    {
        STATS_CLOCK = 1,
        STATS_UNCLOCK = 2,
    };

    ///////////////////////////////////////////////////////////////
    //
    // CStatEvents class
    //
    // For fast storing of clock/unclock event markers
    //
    ///////////////////////////////////////////////////////////////
    class CStatEvents
    {
    public:
        struct SItem
        {
            const char*    szSection;
            const char*    szName;
            eStatEventType type;
            TIMEUS         timeStamp;
        };

        CStatEvents();
        void SetEnabled(bool bEnabled);
        bool ClearBuffer(bool bCanResize);
        void Sample(class SStatCollection& m_StatCollection);

        void Add(const char* szSection, const char* szName, eStatEventType type)
        {
            if (m_BufferPos >= m_BufferPosMaxUsing)
                return;

            SItem& Item = m_ItemBuffer[m_BufferPos++];
            Item.szSection = szSection;
            Item.szName = szName;
            Item.type = type;
            Item.timeStamp = GetTimeUs();
        }

    protected:
        bool               m_bEnabled;
        SItem*             m_ItemBuffer;
        int                m_BufferPos;
        int                m_BufferPosMax;
        int                m_BufferPosMaxUsing;
        std::vector<SItem> m_ItemBufferArray;
    };

    // Global CStatEvents instance
    extern class CStatEvents g_StatEvents;

    // Macros for clocking areas
    #define CLOCK(section,name)     g_StatEvents.Add( section, name, STATS_CLOCK )
    #define UNCLOCK(section,name)   g_StatEvents.Add( section, name, STATS_UNCLOCK )

    // Macro for clocking enclosed code
    #define CLOCK_CALL(section,code) \
        { \
            CLOCK( section, #code ); \
            code; \
            UNCLOCK( section, #code ); \
        }

    // Macros using a common section name
    #define CLOCK_SET_SECTION(tag) \
        const char* szClockSectionTag = tag

    #define CLOCK1(name)        CLOCK( szClockSectionTag, name )
    #define UNCLOCK1(name)      UNCLOCK( szClockSectionTag, name)
    #define CLOCK_CALL1(code)   CLOCK_CALL( szClockSectionTag, code )

    //
    // Performance stat resulting
    //

    // Single result item
    struct SStatResultItem
    {
        constexpr SStatResultItem() noexcept {}

        int   iCounter{0};
        int   iCounterTotal{0};
        int   iCounterTotalAcc{0};
        float fMs{0};
        float fMsMax{0};
        float fMsMaxNext{0};
        float fMsTotal{0};
        float fMsTotalPercent{0};
        float fMsTotalAcc{0};
    };

    // A result section containing result items
    class SStatResultSection : public std::map<std::string, SStatResultItem>
    {
    public:
    };

    // Result collection containing result sections
    class SStatResultCollection : public std::map<std::string, SStatResultSection>
    {
    public:
    };

    ///////////////////////////////////////////////////////////////
    //
    // CStatResults class
    //
    // For compiling and saving data from CStatEvents
    //
    ///////////////////////////////////////////////////////////////
    class CStatResults
    {
    public:
        CStatResults();
        void FrameEnd();

        SStatResultCollection m_CollectionCombo;
        float                 m_fNextMaxClearTime;
    };

}            // namespace SharedUtil
