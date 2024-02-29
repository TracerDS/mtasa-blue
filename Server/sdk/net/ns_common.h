/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        sdk/net/ns_common.h
 *  PURPOSE:     Net common defines
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#include "net/bitstream.h"
#include "net/packetenums.h"
#include "ns_playerid.h"

#include <cstdint>

const NetServerPlayerID NET_INVALID_PLAYER_ID;
#define NET_INVALID_PLAYER_INDEX 255;

#define NET_MAX_PLAYER_COUNT        64
#define NET_MAX_VEHICLE_COUNT       250

#define NET_MAX_PLAYER_NAME_LENGTH  32

typedef struct __static_client_data_t
{
    char szPlayerName[NET_MAX_PLAYER_NAME_LENGTH + 1];
} static_client_data_t, *pstatic_client_data_t;

typedef struct __static_server_data_t
{
} static_server_data_t, *pstatic_server_data_t;

using PPACKETHANDLER = bool (*)(std::uint8_t, const NetServerPlayerID&, NetBitStreamInterface*, SNetExtraInfo*);

enum NetServerPacketPriority
{
    PACKET_PRIORITY_HIGH = 0,
    PACKET_PRIORITY_MEDIUM,
    PACKET_PRIORITY_LOW,
    PACKET_PRIORITY_COUNT
};

enum NetServerPacketReliability
{
    PACKET_RELIABILITY_UNRELIABLE = 0,
    PACKET_RELIABILITY_UNRELIABLE_SEQUENCED,
    PACKET_RELIABILITY_RELIABLE,
    PACKET_RELIABILITY_RELIABLE_ORDERED,
    PACKET_RELIABILITY_RELIABLE_SEQUENCED            //     Can drop packets
};

// Copy of raknet statistics
struct NetRawStatistics
{
    std::uint32_t messageSendBuffer[4];
    std::uint32_t messagesSent[4];
    std::int64_t messageDataBitsSent[4];
    std::int64_t messageTotalBitsSent[4];
    std::uint32_t packetsContainingOnlyAcknowlegements;
    std::uint32_t acknowlegementsSent;
    std::uint32_t acknowlegementsPending;
    std::int64_t acknowlegementBitsSent;
    std::uint32_t packetsContainingOnlyAcknowlegementsAndResends;
    std::uint32_t messageResends;
    std::int64_t messageDataBitsResent;
    std::int64_t messagesTotalBitsResent;
    std::uint32_t messagesOnResendQueue;
    std::uint32_t numberOfUnsplitMessages;
    std::uint32_t numberOfSplitMessages;
    std::uint32_t totalSplits;
    std::uint32_t packetsSent;
    std::int64_t encryptionBitsSent;
    std::int64_t totalBitsSent;
    std::uint32_t sequencedMessagesOutOfOrder;
    std::uint32_t sequencedMessagesInOrder;
    std::uint32_t orderedMessagesOutOfOrder;
    std::uint32_t orderedMessagesInOrder;
    std::uint32_t packetsReceived;
    std::uint32_t packetsWithBadCRCReceived;
    std::int64_t bitsReceived;
    std::int64_t bitsWithBadCRCReceived;
    std::uint32_t acknowlegementsReceived;
    std::uint32_t duplicateAcknowlegementsReceived;
    std::uint32_t messagesReceived;
    std::uint32_t invalidMessagesReceived;
    std::uint32_t duplicateMessagesReceived;
    std::uint32_t messagesWaitingForReassembly;
    std::uint32_t internalOutputQueueSize;
    double    bitsPerSecond;
    std::int64_t connectionStartTime;
    bool      bandwidthExceeded;
};

struct NetStatistics
{
    // Needed for getNetworkStats()
    std::uint64_t bytesReceived;
    std::uint64_t bytesSent;
    std::uint32_t packetsReceived;
    std::uint32_t packetsSent;
    std::uint32_t messagesInSendBuffer;
    std::uint32_t messagesInResendBuffer;
    bool          isLimitedByCongestionControl;
    bool          isLimitedByOutgoingBandwidthLimit;
    float         packetlossTotal;
    float         packetlossLastSecond;

    // Copy of raknet statistics
    NetRawStatistics raw;
};

struct SBandwidthStatistics
{
    std::int64_t llOutgoingUDPByteCount;
    std::int64_t llIncomingUDPByteCount;
    std::int64_t llIncomingUDPByteCountBlocked;
    std::int64_t llOutgoingUDPPacketCount;
    std::int64_t llIncomingUDPPacketCount;
    std::int64_t llIncomingUDPPacketCountBlocked;
    std::int64_t llOutgoingUDPByteResentCount;
    std::int64_t llOutgoingUDPMessageResentCount;
    SThreadCPUTimes threadCPUTimes;
};

struct SNetPerformanceStatistics
{
    std::uint32_t uiUpdateCycleRecvTimeAvgUs;
    std::uint32_t uiUpdateCycleSendTimeAvgUs;
    std::uint32_t uiUpdateCycleRecvTimeMaxUs;
    std::uint32_t uiUpdateCycleSendTimeMaxUs;
    std::uint32_t uiUpdateCycleRecvDatagramsMax;
    std::uint32_t uiUpdateCycleDatagramsMax;
    std::uint32_t uiUpdateCycleDatagramsLimit;
    std::uint32_t uiUpdateCycleMessagesMax;
    std::uint32_t uiUpdateCycleMessagesLimit;
    std::uint32_t uiUpdateCycleSendsLimitedTotal;
    float         fUpdateCycleSendsLimitedPercent;
    float         fUpdateCycleRecvDatagramsAvg;
    float         fUpdateCycleDatagramsAvg;
    float         fUpdateCycleMessagesAvg;
};

struct SSyncThreadStatistics
{
    std::uint32_t uiRecvTimeAvgUs;
    std::uint32_t uiSendTimeAvgUs;
    std::uint32_t uiRecvTimeMaxUs;
    std::uint32_t uiSendTimeMaxUs;
    std::uint32_t uiRecvMsgsMax;
    std::uint32_t uiSendCmdsMax;
    float         fRecvMsgsAvg;
    float         fSendCmdsAvg;
};

enum ePacketOrdering
{
    PACKET_ORDERING_DEFAULT = 0,
    PACKET_ORDERING_CHAT,
    PACKET_ORDERING_DATA_TRANSFER,
    PACKET_ORDERING_VOICE,
};

// Typedefs to make shared code easier (?????)
/*
using NetPlayerID = NetServerPlayerID;
using NetPacketPriority = NetServerPacketPriority;
using NetPacketReliability = NetServerPacketReliability;
*/
