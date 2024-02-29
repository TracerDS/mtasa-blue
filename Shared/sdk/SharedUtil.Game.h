/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        SharedUtil.Game.h
 *  PURPOSE:     Shared stuff which is game oriented
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/
#pragma once

#include "SharedUtil.Misc.h"

namespace SharedUtil
{
    namespace TrafficLight
    {
        enum EColor
        {
            GREEN,
            YELLOW,
            RED
        };

        enum EState
        {
            AUTO,
            DISABLED,
        };
    }            // namespace TrafficLight

    std::uint8_t GetTrafficLightStateFromColors(TrafficLight::EColor eColorNS, TrafficLight::EColor eColorEW);

    class CVehicleColor
    {
    public:
        CVehicleColor();

        void SetRGBColors(SColor color1, SColor color2, SColor color3, SColor color4);
        void SetPaletteColors(std::uint8_t ucColor1, std::uint8_t ucColor2, std::uint8_t ucColor3, std::uint8_t ucColor4);

        void SetRGBColor(std::uint32_t uiSlot, SColor color);
        void SetPaletteColor(std::uint32_t uiSlot, std::uint8_t ucColor);

        SColor GetRGBColor(std::uint32_t uiSlot);
        std::uint8_t  GetPaletteColor(std::uint32_t uiSlot);

        int GetNumColorsUsed();

        static std::uint8_t  GetPaletteIndexFromRGB(SColor color);
        static SColor GetRGBFromPaletteIndex(std::uint8_t ucColor);

    protected:
        void InvalidatePaletteColors();
        void ValidatePaletteColors();
        void InvalidateRGBColors();
        void ValidateRGBColors();

        SColor m_RGBColors[4];
        std::uint8_t  m_ucPaletteColors[4];
        bool   m_bPaletteColorsWrong;
        bool   m_bRGBColorsWrong;
    };

    struct SHeatHazeSettings
    {
        constexpr SHeatHazeSettings() noexcept {}

        std::uint8_t  ucIntensity{0};            //     0 to 255
        std::uint8_t  ucRandomShift{0};            //     0 to 255
        std::uint16_t usSpeedMin{1};               //     0 to 1000
        std::uint16_t usSpeedMax{1};               //     0 to 1000
        short  sScanSizeX{1};               // -1000 to 1000
        short  sScanSizeY{1};               // -1000 to 1000
        std::uint16_t usRenderSizeX{1};            //     0 to 1000
        std::uint16_t usRenderSizeY{1};            //     0 to 1000
        bool bInsideBuilding{false};
    };

    namespace EDiagnosticDebug
    {
        enum EDiagnosticDebugType
        {
            NONE,
            GRAPHICS_6734,
            BIDI_6778,
            D3D_6732,
            LOG_TIMING_0000,
            JOYSTICK_0000,
            LUA_TRACE_0000,
            RESIZE_ALWAYS_0000,
            RESIZE_NEVER_0000,
            MAX,
        };
    };

    using EDiagnosticDebug::EDiagnosticDebugType;

    // Common strings for SetApplicationSetting
    #define DIAG_PRELOAD_UPGRADES_SLOW          "diagnostics", "preloading-upgrades-slow"
    #define DIAG_PRELOAD_UPGRADE_ATTEMPT_ID     "diagnostics", "preloading-upgrade-attempt-id"
    #define DIAG_PRELOAD_UPGRADES_LOWEST_UNSAFE "diagnostics", "preloading-upgrades-lowest-unsafe"
    #define DIAG_PRELOAD_UPGRADES_HISCORE       "diagnostics", "preloading-upgrades-hiscore"
    #define DIAG_CRASH_EXTRA_MSG                "diagnostics", "last-crash-reason"
    #define DIAG_MINIDUMP_DETECTED_COUNT        "diagnostics", "num-minidump-detected"
    #define DIAG_MINIDUMP_CONFIRMED_COUNT       "diagnostics", "num-minidump-confirmed"
    #define DIAG_BSOD_DETECT_SKIP               "diagnostics", "bsod-detect-skip"
    #define GENERAL_PROGRESS_ANIMATION_DISABLE  "progress-animation-disable"

    // Common strings for watchdog detections
    #define WD_SECTION_PRELOAD_UPGRADES                     "preload-upgrades"
    #define WD_SECTION_NOT_CLEAN_GTA_EXIT                   "L0"                // Opened in loader, closed if GTA exits with no error
    #define WD_SECTION_NOT_STARTED_ONLINE_GAME              "L1"                // Opened in loader, closed when online game has started
    #define WD_SECTION_NOT_SHOWN_LOADING_SCREEN             "L2"                // Opened in loader, closed when loading screen is shown
    #define WD_SECTION_STARTUP_FREEZE                       "L3"                // Opened in loader, closed when loading screen is shown, or a startup problem is handled elsewhere
    #define WD_SECTION_NOT_USED_MAIN_MENU                   "L4"                // Opened in loader, closed when main menu is used
    #define WD_SECTION_POST_INSTALL                         "L5"                // Opened in when installer runs, closed when main menu is used
    #define WD_SECTION_IS_QUITTING                          "Q0"                // Open during quit
    #define WD_COUNTER_CRASH_CHAIN_BEFORE_ONLINE_GAME       "CR1"               // Counts consecutive crashes before the online game starts
    #define WD_COUNTER_CRASH_CHAIN_BEFORE_LOADING_SCREEN    "CR2"               // Counts consecutive crashes before the loading screen is shown
    #define WD_COUNTER_CRASH_CHAIN_BEFORE_USED_MAIN_MENU    "CR3"               // Counts consecutive crashes before the main menu is used
}            // namespace SharedUtil
