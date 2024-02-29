/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        CDuplicateLineFilter.h
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/
#pragma once

#include <list>
#include <deque>

template <class T>
class CDuplicateLineFilter
{
public:
    struct SOutputLine : public T
    {
        SOutputLine(const T& line, std::uint32_t uiCount) noexcept : T(line), uiDupCount(uiCount) {}
        std::uint32_t uiDupCount;
    };

    CDuplicateLineFilter(std::uint32_t uiMaxNumOfLinesInMatch = 4, std::uint32_t uiMaxDelaySeconds = 5) noexcept
    {
        m_uiMaxNumOfLinesInMatch = uiMaxNumOfLinesInMatch;
        m_uiMaxDelaySeconds = uiMaxDelaySeconds;
    }

    //////////////////////////////////////////////////////////
    //
    // AddLine
    //
    //////////////////////////////////////////////////////////
    void AddLine(const T& line)
    {
        if (!m_bIsMatching)
        {
            // Not currently matching
            // Search history for first line of new match
            for (std::uint32_t i = 0; i < m_History.size(); i++)
            {
                if (line == m_History.at(i))
                {
                    // Begin match
                    m_bIsMatching = true;
                    m_uiMatchSize = i + 1;
                    m_uiMatchCurLine = i;
                    m_uiDupCount = 0;
                    if (m_uiMatchCurLine == 0)
                        m_uiDupCount++;            // Completed matching set (will only occur here for single line match)
                    return;
                }
            }
        }
        else
        {
            // Is currently matching
            // Check if match will continue
            std::uint32_t uiNextLine = (m_uiMatchCurLine - 1 + m_uiMatchSize) % m_uiMatchSize;
            if (line == m_History.at(uiNextLine))
            {
                // Still matching
                m_uiMatchCurLine = uiNextLine;
                if (m_uiMatchCurLine == 0)
                    m_uiDupCount++;            // Completed matching set
                return;
            }
            else
            {
                // Match finished
                Flush();
            }
        }

        // Not matching
        // Update history
        m_History.push_front(line);
        while (m_History.size() > m_uiMaxNumOfLinesInMatch)
            m_History.pop_back();
        // Push line to output
        AddLineToOutputBuffer(line);
    }

    //////////////////////////////////////////////////////////
    //
    // Flush
    //
    // Finish current match and push relevant lines to the output buffer
    //
    //////////////////////////////////////////////////////////
    void Flush()
    {
        if (!m_bIsMatching)
            return;

        m_bIsMatching = false;

        // Handle full set matches
        if (m_uiDupCount > 0)
        {
            for (std::uint32_t i = 0; i < m_uiMatchSize; i++)
            {
                AddLineToOutputBuffer(m_History.at(m_uiMatchSize - 1 - i), m_uiDupCount);
            }
        }

        // Handle partial set matches
        if (m_uiMatchCurLine > 0)
        {
            for (std::uint32_t i = 0; i < m_uiMatchSize - m_uiMatchCurLine; i++)
            {
                AddLineToOutputBuffer(m_History.at(m_uiMatchSize - 1 - i));
            }
        }
        m_History.clear();
    }

    //////////////////////////////////////////////////////////
    //
    // AddLineToOutputBuffer
    //
    //////////////////////////////////////////////////////////
    void AddLineToOutputBuffer(const T& line, std::uint32_t uiDupCount = 0) { m_PendingOutput.push_back(SOutputLine(line, uiDupCount)); }

    //////////////////////////////////////////////////////////
    //
    // PopOutputLine
    //
    // Returns true if has populated values
    //
    //////////////////////////////////////////////////////////
    bool PopOutputLine(T& outLine)
    {
        if (m_PendingOutput.empty())
        {
            if (time(nullptr) - m_tLastOutputTime > m_uiMaxDelaySeconds)
                Flush();
            if (m_PendingOutput.empty())
                return false;
        }
        m_tLastOutputTime = time(nullptr);

        const SOutputLine& line = m_PendingOutput.front();
        outLine = line;
        if (line.uiDupCount > 1)
            outLine += SString("  [DUP x%u]", line.uiDupCount);
        m_PendingOutput.pop_front();
        return true;
    }

protected:
    std::deque<T>          m_History;
    std::list<SOutputLine> m_PendingOutput;
    bool                   m_bIsMatching = false;            // true if matching a duplicate set
    std::uint32_t          m_uiMatchSize = 0;                // Number of lines in active match
    std::uint32_t          m_uiMatchCurLine = 0;             // Current line in active match
    std::uint32_t          m_uiDupCount = 0;                 // Number of duplicates found for active match
    time_t                 m_tLastOutputTime = 0;
    std::uint32_t          m_uiMaxNumOfLinesInMatch;            // Max number lines in a matching set
    std::uint32_t          m_uiMaxDelaySeconds;                 // Max seconds to delay outputting duplicated lines
};
