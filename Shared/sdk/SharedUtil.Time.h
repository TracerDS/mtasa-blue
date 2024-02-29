/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        SharedUtil.Time.h
 *  PURPOSE:
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/
#pragma once
#include <chrono>
#include "SharedUtil.Misc.h"
#include "SString.h"

#ifdef min
    #undef min
#endif
#ifdef max
    #undef max
#endif

namespace SharedUtil
{
    //
    // Retrieves the number of milliseconds that have elapsed since the function was first called (plus a little bit to make it look good).
    // This keeps the counter as low as possible to delay any precision or wrap around issues.
    // Note: Return value is module dependent
    //
    std::uint32_t GetTickCount32();

    // Forbid use of GetTickCount
    #define GetTickCount GetTickCount_has_been_replaced_with_GetTickCount32
    #define GetTickCount64 GetTickCount64_wont_work_on_XP_you_IDIOT

    //
    // Retrieves the number of milliseconds that have elapsed since some arbitrary point in time.
    //
    // GetTickCount64() exists on Vista and up and is like GetTickCount() except it returns
    // an __int64 and will effectively never wrap. This is an emulated version for XP and down.
    // Note: Wrap around issue is only defeated if the gap between calls is less than 24 days.
    //
    std::int64_t GetTickCount64_();

    //
    // Retrieves the number of seconds that have elapsed since some arbitrary point in time.
    //
    double GetSecondCount();

    //
    // Get the time as a sortable string.
    // Set bDate to include the date, bMs to include milliseconds
    // Return example: "2010-09-01 14:54:31.091"
    SString GetTimeString(bool bDate = false, bool bMilliseconds = false, bool bLocal = false);

    // Get the local time as a sortable string.
    SString GetLocalTimeString(bool bDate = false, bool bMilliseconds = false);

    // Get time in microseconds
    using TIMEUS = std::uint32_t;
    TIMEUS        GetTimeUs();

    // Get tick count cached per module
    std::int64_t GetModuleTickCount64();
    void      UpdateModuleTickCount64();

    // Debugging
    void AddTickCount(std::int64_t llTickCountAdd);

    //
    // Encapsulate a tick count value
    //
    class CTickCount
    {
        std::int64_t m_llTicks = 0;

    public:
        // Constructors
        CTickCount() noexcept {}
        explicit CTickCount(std::int64_t llTicks) noexcept : m_llTicks(llTicks) {}
        explicit CTickCount(double dTicks) noexcept : m_llTicks(static_cast<std::int64_t>(dTicks)) {}

        // Operators
        CTickCount  operator+(const CTickCount& other) const noexcept { return CTickCount(m_llTicks + other.m_llTicks); }
        CTickCount  operator-(const CTickCount& other) const noexcept { return CTickCount(m_llTicks - other.m_llTicks); }
        CTickCount& operator+=(const CTickCount& other) noexcept
        {
            m_llTicks += other.m_llTicks;
            return *this;
        }
        CTickCount& operator-=(const CTickCount& other) noexcept
        {
            m_llTicks -= other.m_llTicks;
            return *this;
        }

        // Comparison
        bool operator<(const CTickCount& other) const noexcept { return m_llTicks < other.m_llTicks; }
        bool operator>(const CTickCount& other) const noexcept { return m_llTicks > other.m_llTicks; }
        bool operator<=(const CTickCount& other) const noexcept { return m_llTicks <= other.m_llTicks; }
        bool operator>=(const CTickCount& other) const noexcept { return m_llTicks >= other.m_llTicks; }
        bool operator==(const CTickCount& other) const noexcept { return m_llTicks == other.m_llTicks; }
        bool operator!=(const CTickCount& other) const noexcept { return m_llTicks != other.m_llTicks; }

        // Conversion
        double       ToDouble() const noexcept { return static_cast<double>(m_llTicks); }
        std::int64_t ToLongLong() const noexcept { return m_llTicks; }
        int          ToInt() const noexcept { return static_cast<int>(m_llTicks); }

        // Static functions
        static CTickCount Now(bool bUseModuleTickCount = false) noexcept {
            return CTickCount(bUseModuleTickCount ? GetModuleTickCount64() : GetTickCount64_());
        }
    };

    //
    // Simple class to measure time passing
    // Main feature is the limit on how much time is allowed to pass between each Get()
    //
    class CElapsedTime
    {
    public:
        // MaxIncrement should be set higher than the expected tick interval between Get() calls
        CElapsedTime() noexcept
        {
            Reset();
        }

        void SetMaxIncrement(long lMaxIncrement, bool bUseModuleTickCount = false) noexcept
        {
            m_llMaxIncrement = lMaxIncrement;
            m_bUseModuleTickCount = bUseModuleTickCount;
        }

        void SetUseModuleTickCount(bool bUseModuleTickCount) noexcept {
            m_bUseModuleTickCount = bUseModuleTickCount;
        }

        void Reset() noexcept
        {
            m_llUpdateTime = DoGetTickCount();
            m_ullElapsedTime = 0;
        }

        std::uint64_t Get() noexcept
        {
            std::int64_t llTime = DoGetTickCount();
            m_ullElapsedTime += Clamp(0LL, llTime - m_llUpdateTime, m_llMaxIncrement);
            m_llUpdateTime = llTime;
            return m_ullElapsedTime;
        }

    protected:
        std::int64_t DoGetTickCount() const noexcept {
            return m_bUseModuleTickCount ? GetModuleTickCount64() : GetTickCount64_();
        }

        std::int64_t  m_llUpdateTime;
        std::uint64_t m_ullElapsedTime;
        std::int64_t  m_llMaxIncrement = INT_MAX;
        bool          m_bUseModuleTickCount = false;
    };

    //
    // Like CElapsedTime except it is not as accurate.
    // Has a lot better Get() performance than CElapsedTime as counting is done in another thread.
    //
    class CElapsedTimeApprox
    {
    public:
        CElapsedTimeApprox() noexcept
        {
    #ifndef SHARED_UTIL_MANUAL_TIMER_INITIALIZATION
            StaticInitialize(this);
    #endif
        }

        ~CElapsedTimeApprox() noexcept
        {
            if (!m_ppIntervalCounter || !*m_ppIntervalCounter)
                return;
            if ((*m_ppIntervalCounter)->Release())
                return;
            *m_ppIntervalCounter = nullptr;
        }

        void SetMaxIncrement(std::uint32_t uiMaxIncrement) noexcept { m_uiMaxIncrement = uiMaxIncrement; }

        void Reset() noexcept
        {
            m_ucUpdateCount = DoGetCount();
            m_uiElapsedTime = 0;
        }

        // This will wrap if gap between calls is over 25.5 seconds
        std::uint32_t Get() noexcept
        {
            std::uint8_t ucCount = DoGetCount();
            std::uint32_t  uiTimeDelta = (ucCount - m_ucUpdateCount) * 100U;
            m_ucUpdateCount = ucCount;
            m_uiElapsedTime += std::min(uiTimeDelta, m_uiMaxIncrement);
            return m_uiElapsedTime;
        }

        static void StaticInitialize(CElapsedTimeApprox* pTimer);

    protected:
        std::uint8_t DoGetCount() const noexcept { return *m_pucCounterValue; }

        bool            m_bInitialized = false;
        std::uint8_t    m_ucUpdateCount = 0;
        std::uint32_t   m_uiMaxIncrement = INT_MAX;
        std::uint32_t   m_uiElapsedTime = 0;
        std::uint8_t*   m_pucCounterValue = nullptr;
        CRefCountable** m_ppIntervalCounter = nullptr;
    };

    //
    // Measure time passing with microsecond resolution
    //
    class CElapsedTimeHD
    {
    public:
        CElapsedTimeHD() noexcept { Reset(); }

        void Reset() noexcept { m_resetTime = DoGetTickCount(); }

        // Returns time in milliseconds since last reset
        double Get() const noexcept
        {
            std::chrono::duration<double, std::micro> elapsedTime = DoGetTickCount() - m_resetTime;
            return elapsedTime.count() / 1000.0;
        }

    protected:
        std::chrono::high_resolution_clock::time_point DoGetTickCount() const noexcept {
            return std::chrono::high_resolution_clock::now();
        }

        std::chrono::high_resolution_clock::time_point m_resetTime;
    };

    //
    // Timing sections of code
    //
    template <int RESERVE_NUM_ITEMS = 20>
    class CTimeUsMarker
    {
    public:
        struct SItem
        {
            const char* szDesc;
            TIMEUS      timeUs;
        };

        CTimeUsMarker() noexcept { itemList.reserve(RESERVE_NUM_ITEMS); }

        void Set(const char* szDesc) noexcept
        {
            itemList.push_back(SItem());
            SItem& item = itemList.back();
            item.timeUs = GetTimeUs();
            item.szDesc = szDesc;
        }

        void SetAndStoreString(const SString& strDesc) noexcept
        {
            stringStoreList.push_back(strDesc);
            Set(stringStoreList.back());
        }

        SString GetString() const noexcept
        {
            SString strStatus;
            for (std::uint32_t i = 1; i < itemList.size(); i++)
            {
                const SItem& itemPrev = itemList[i - 1];
                const SItem& item = itemList[i];
                strStatus += SString("[%0.2fms %s] ", (item.timeUs - itemPrev.timeUs) / 1000.f, item.szDesc);
            }
            return strStatus;
        }

    protected:
        std::list<SString> stringStoreList;
        std::vector<SItem> itemList;
    };

}            // namespace SharedUtil
