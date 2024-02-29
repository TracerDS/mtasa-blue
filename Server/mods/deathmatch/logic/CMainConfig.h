/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/deathmatch/logic/CMainConfig.h
 *  PURPOSE:     XML-based main configuration file parser class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

class CMainConfig;

#pragma once

#include "CCommon.h"
#include "CLogger.h"
#include "CConsole.h"
#include "CXMLConfig.h"
#include <list>

#define MAX_MAP_NAME_LENGTH 64

class CMainConfig;
class CCommandLineParser;
class CLuaArguments;

using PFN_SettingChangeCallback = void (CMainConfig::*)();

struct SIntSetting
{
    bool                      bSettable;
    bool                      bSavable;
    int                       iMin;
    int                       iDefault;
    int                       iMax;
    const char*               szName;
    int*                      pVariable;
    PFN_SettingChangeCallback changeCallback;
};

class CMainConfig : public CXMLConfig
{
public:
    ZERO_ON_NEW
    CMainConfig(CConsole* pConsole);

    bool Load();
    bool LoadExtended();
    bool Save();

    const std::string& GetServerName() const noexcept { return m_strServerName; };
    SString            GetServerIP() const noexcept;
    SString            GetServerIPList() const noexcept;
    std::uint16_t      GetServerPort() const noexcept;
    std::uint32_t      GetMaxPlayers() const noexcept;
    std::uint32_t      GetHardMaxPlayers() const noexcept;
    void               SetSoftMaxPlayers(std::uint32_t v) noexcept { m_uiSoftMaxPlayers = v; }
    bool               IsHTTPEnabled() const noexcept { return m_bHTTPEnabled; };

    bool               IsValidPassword(const char* szPassword) const noexcept;
    bool               HasPassword() const noexcept { return !m_strPassword.empty(); };
    const std::string& GetPassword() const noexcept { return m_strPassword; };
    bool               SetPassword(const char* szPassword, bool bSave) noexcept;

    bool          IsVoiceEnabled() const noexcept;
    std::uint32_t GetVoiceSampleRate() const noexcept { return m_uiVoiceSampleRate; };
    std::uint32_t GetVoiceQuality() const noexcept { return m_ucVoiceQuality; };
    std::uint32_t GetVoiceBitrate() const noexcept { return m_uiVoiceBitrate; };

    bool                         GetAseInternetPushEnabled() const noexcept { return m_iAseMode == 2 && !IsFakeLagCommandEnabled(); }
    bool                         GetAseInternetListenEnabled() const noexcept { return m_iAseMode == 1 && !IsFakeLagCommandEnabled(); }
    bool                         GetAseLanListenEnabled() const noexcept { return m_bDontBroadcastLan ? false : true; }
    std::uint16_t                GetHTTPPort() const noexcept;
    eHTTPDownloadType            GetHTTPDownloadType() const noexcept { return m_ucHTTPDownloadType; };
    const std::string&           GetHTTPDownloadURL() const noexcept { return m_strHTTPDownloadURL; };
    int                          GetHTTPMaxConnectionsPerClient() const noexcept { return m_iHTTPMaxConnectionsPerClient; };
    int                          GetHTTPThreadCount() const noexcept { return m_iHTTPThreadCount; };
    int                          GetHTTPDosThreshold() const noexcept { return m_iHTTPDosThreshold; };
    const SString&               GetHTTPDosExclude() const noexcept { return m_strHTTPDosExclude; };
    int                          GetEnableClientChecks() const noexcept { return m_iEnableClientChecks; };
    const std::string&           GetLogFile() const noexcept { return m_strLogFile; };
    const std::string&           GetAuthFile() const noexcept { return m_strAuthFile; };
    bool                         GetJoinFloodProtectionEnabled() const noexcept { return m_bJoinFloodProtectionEnabled; };
    bool                         GetScriptDebugLogEnabled() const noexcept { return m_bScriptDebugLogEnabled && !m_strScriptDebugLogFile.empty(); };
    const std::string&           GetScriptDebugLogFile() const noexcept { return m_strScriptDebugLogFile; };
    std::uint32_t                GetScriptDebugLogLevel() const noexcept { return m_uiScriptDebugLogLevel; };
    const std::string&           GetAccessControlListFile() const noexcept { return m_strAccessControlListFile; };
    bool                         GetSerialVerificationEnabled() const noexcept { return m_bVerifySerials; };
    bool                         IsDisableAC(const char* szTagAC) const noexcept { return MapContains(m_DisableComboACMap, szTagAC); };
    bool                         IsEnableDiagnostic(const char* szTag) const noexcept { return MapContains(m_EnableDiagnosticMap, szTag); };
    CMtaVersion                  GetMinClientVersion() const noexcept { return m_strMinClientVersion; }
    const CMtaVersion&           GetRecommendedClientVersion() const noexcept { return m_strRecommendedClientVersion; }
    int                          GetMinClientVersionAutoUpdate() const noexcept { return m_iMinClientVersionAutoUpdate; }
    const SString&               GetIdFile() const noexcept { return m_strIdFile; }
    bool                         GetThreadNetEnabled() const noexcept { return m_bThreadNetEnabled; }
    const SString&               GetGlobalDatabasesPath() const noexcept { return m_strGlobalDatabasesPath; }
    const SString&               GetSystemDatabasesPath() const noexcept { return m_strSystemDatabasesPath; }
    const SString&               GetBackupPath() const noexcept { return m_strBackupPath; }
    int                          GetBackupInterval() const noexcept { return m_iBackupInterval; }
    int                          GetBackupAmount() const noexcept { return m_iBackupAmount; }
    void                         NotifyDidBackup() noexcept;
    bool                         ShouldCompactInternalDatabases() const noexcept;
    std::uint16_t                GetFPSLimit() const noexcept { return m_usFPSLimit; };
    bool                         SetFPSLimit(std::uint16_t usFPS, bool bSave) noexcept;
    int                          GetPendingWorkToDoSleepTime() const noexcept;
    int                          GetNoWorkToDoSleepTime() const noexcept;
    int                          GetServerLogicFpsLimit() const noexcept { return m_iServerLogicFpsLimit; };
    const SString&               GetDbLogFilename() noexcept { return m_strDbLogFilename; }
    bool                         GetSyncMapElementData() const noexcept { return m_bSyncMapElementData; }
    void                         SetSyncMapElementData(bool bOn) noexcept { m_bSyncMapElementData = bOn; }
    bool                         GetBulletSyncEnabled() const noexcept { return m_bBulletSyncEnabled != 0; }
    int                          GetVehExtrapolatePercent() const noexcept { return m_iVehExtrapolatePercent; }
    int                          GetVehExtrapolatePingLimit() const noexcept { return m_iVehExtrapolatePingLimit; }
    bool                         GetUseAltPulseOrder() const noexcept { return m_bUseAltPulseOrder != 0; }
    const SString&               GetLoadstringLogFilename() const noexcept { return m_strLoadstringLogFilename; }
    bool                         GetLoadstringLogEnabled() const noexcept { return !m_strLoadstringLogFilename.empty(); }
    bool                         GetCrashDumpUploadEnabled() const noexcept { return m_bCrashDumpUploadEnabled != 0; }
    bool                         GetFilterDuplicateLogLinesEnabled() const noexcept { return m_bFilterDuplicateLogLinesEnabled != 0; }
    bool                         IsAuthSerialGroup(const SString& strGroup) const noexcept { return ListContains(m_AuthSerialGroupList, strGroup); };
    bool IsAuthSerialHttpIpException(const SString& strIp) const noexcept { return ListContains(m_AuthSerialHttpIpExceptionList, strIp); }
    bool                         GetAuthSerialEnabled() const noexcept { return !m_AuthSerialGroupList.empty(); };
    bool                         GetAuthSerialHttpEnabled() const noexcept { return m_bAuthSerialHttpEnabled && GetAuthSerialEnabled(); };
    const std::vector<SString>&  GetAuthSerialGroupList() const noexcept { return m_AuthSerialGroupList; }
    const std::vector<SString>&  GetAuthSerialHttpIpExceptionList() const noexcept { return m_AuthSerialHttpIpExceptionList; }
    const std::vector<SString>&  GetOwnerEmailAddressList() const noexcept { return m_OwnerEmailAddressList; }
    bool                         IsDatabaseCredentialsProtectionEnabled() const noexcept { return m_bDatabaseCredentialsProtectionEnabled != 0; }
    bool                         IsFakeLagCommandEnabled() const noexcept { return m_bFakeLagCommandEnabled != 0; }

    SString GetSetting(const SString& configSetting);
    bool    GetSetting(const SString& configSetting, SString& strValue);
    bool    SetSetting(const SString& configSetting, const SString& strValue, bool bSave);
    bool    GetSettingTable(const SString& strName, CLuaArguments* outTable);

    void               SetCommandLineParser(CCommandLineParser* pCommandLineParser);
    void               ApplyNetOptions();
    void               ApplyBandwidthReductionMode();
    void               ApplyThreadNetEnabled();
    void               SetFakeLag(int iPacketLoss, int iExtraPing, int iExtraPingVary, int iKBPSLimit);
    const SNetOptions& GetNetOptions() const noexcept { return m_NetOptions; }

    const std::vector<SIntSetting>& GetIntSettingList();
    void                            OnTickRateChange();
    void                            OnAseSettingChange();
    void                            OnPlayerTriggeredEventIntervalChange();

    int GetPlayerTriggeredEventInterval() const noexcept { return m_iPlayerTriggeredEventIntervalMs; }
    int GetMaxPlayerTriggeredEventsPerInterval() const noexcept { return m_iMaxPlayerTriggeredEventsPerInterval; }

private:
    void RegisterCommand(const char* szName, FCommandHandler* pFunction, bool bRestricted, const char* szConsoleHelpText);
    bool GetSettingTable(const SString& strName, const char** szAttribNames, std::uint32_t uiNumAttribNames, CLuaArguments* outTable);
    bool AddMissingSettings();

    CConsole*           m_pConsole;
    CXMLNode*           m_pRootNode;
    CCommandLineParser* m_pCommandLineParser;

    std::uint32_t m_uiVoiceSampleRate;
    std::uint8_t  m_ucVoiceQuality;
    std::uint32_t m_uiVoiceBitrate;

    bool                       m_bVoiceEnabled;
    std::string                m_strServerIP;
    std::string                m_strServerName;
    std::uint16_t              m_usServerPort;
    std::uint32_t              m_uiHardMaxPlayers;
    std::uint32_t              m_uiSoftMaxPlayers;
    bool                       m_bHTTPEnabled;
    std::string                m_strPassword;
    int                        m_iAseMode;
    int                        m_iUpdateCycleDatagramsLimit;
    int                        m_iUpdateCycleMessagesLimit;
    std::uint16_t              m_usHTTPPort;
    eHTTPDownloadType          m_ucHTTPDownloadType;
    std::string                m_strHTTPDownloadURL;
    int                        m_iHTTPMaxConnectionsPerClient;
    int                        m_iHTTPThreadCount;
    int                        m_iHTTPDosThreshold;
    SString                    m_strHTTPDosExclude;
    int                        m_iEnableClientChecks;
    std::string                m_strLogFile;
    std::string                m_strAuthFile;
    bool                       m_bJoinFloodProtectionEnabled;
    bool                       m_bScriptDebugLogEnabled;
    std::string                m_strScriptDebugLogFile;
    std::uint32_t              m_uiScriptDebugLogLevel;
    std::string                m_strAccessControlListFile;
    bool                       m_bVerifySerials;
    std::uint16_t              m_usFPSLimit;
    int                        m_bDontBroadcastLan;
    std::set<SString>          m_DisableComboACMap;
    std::set<SString>          m_EnableDiagnosticMap;
    std::vector<SString>       m_AuthSerialGroupList;
    bool                       m_bAuthSerialHttpEnabled;
    std::vector<SString>       m_AuthSerialHttpIpExceptionList;
    std::vector<SString>       m_OwnerEmailAddressList;
    CMtaVersion                m_strMinClientVersion;
    CMtaVersion                m_strRecommendedClientVersion;
    SString                    m_strIdFile;
    SString                    m_strGlobalDatabasesPath;
    SString                    m_strSystemDatabasesPath;
    SString                    m_strBackupPath;
    SString                    m_strDbLogFilename;
    int                        m_iBackupInterval;
    int                        m_iBackupAmount;
    int                        m_iCompactInternalDatabases;
    bool                       m_bDidBackup;
    SString                    m_strBandwidthReductionMode;
    int                        m_iPendingWorkToDoSleepTime;
    int                        m_iNoWorkToDoSleepTime;
    bool                       m_bThreadNetEnabled;
    bool                       m_bSyncMapElementData;
    int                        m_bBulletSyncEnabled;
    std::map<SString, SString> m_TransientSettings;
    SNetOptions                m_NetOptions;
    int                        m_iVehExtrapolatePercent;
    int                        m_iVehExtrapolatePingLimit;
    int                        m_bUseAltPulseOrder;
    int                        m_bNetAutoFilter;
    SString                    m_strLoadstringLogFilename;
    int                        m_iMinClientVersionAutoUpdate;
    int                        m_iServerLogicFpsLimit;
    int                        m_bCrashDumpUploadEnabled;
    int                        m_bFilterDuplicateLogLinesEnabled;
    int                        m_bDatabaseCredentialsProtectionEnabled;
    int                        m_bFakeLagCommandEnabled;
    int                        m_iPlayerTriggeredEventIntervalMs;
    int                        m_iMaxPlayerTriggeredEventsPerInterval;
};
