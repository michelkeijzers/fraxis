// @file Log.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Log.hpp"
#include "../../M00_System/Queues/DiagnosticsQueueWriter.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
#include <cstdio>
#include <array>
#ifndef ESP_PLATFORM
#include <Windows.h>
#endif

namespace M90::Log
{
    static constexpr bool Log_ENABLED = true; // NOSONAR: needs to before the include

    Log::Log(
        M90::Time::ITimeUtilities& timeUtilities)
    :
        _logLevels(0xFFFFFFFF),
        _diagnosticsQueue(nullptr),
        _diagnosticsQueueWriter(nullptr),
        _buffer {},
        _indentation(0),
        _timeUtilities(timeUtilities)
    {
        // No actions required.
    }

    uint32_t Log::GetLogLevels()
    {
        return _logLevels;
    }

    void Log::SetLogLevels(
        uint32_t logLevels)
    {
        _logLevels = logLevels;
    }

    void Log::SetDiagnostics(
        DiagnosticsQueue& diagnosticsQueue,
        DiagnosticsQueueWriter& diagnosticsQueueWriter)
    {
        _diagnosticsQueue = &diagnosticsQueue;
        _diagnosticsQueueWriter = &diagnosticsQueueWriter;
    }

    void Log::Entry(
        Types::ETaskId taskId,
        std::string_view name)
    {
        if (Log_ENABLED)
        {
            // NOLINTNEXTLINE(modernize-use-std-format)
            snprintf( // NOSONAR S6494: std::format not usable on ESP32
                _buffer.data(), _buffer.size(), "%*s>%s\n", _indentation * 2, "", name.data());
            OutputBuffer(taskId, Types::ELogLevel::Debug);
            _indentation++;
        }
    }

    void Log::Exit(
        Types::ETaskId taskId,
        std::string_view name)
    {
        if (Log_ENABLED)
        {
            _indentation--;
            // NOLINTNEXTLINE(modernize-use-std-format)
            snprintf( // NOSONAR S6494: std::format not usable on ESP32
                _buffer.data(), _buffer.size(), "%*s<%s\n", _indentation * 2, "", name.data());
            OutputBuffer(taskId, Types::ELogLevel::Debug);
        }
    }

    void Log::Pointer(
        Types::ETaskId taskId,
        std::string_view name, const void* pointer) // NOSONAR: void* to be flexible
    {
        if (Log_ENABLED)
        {
            // NOLINTNEXTLINE(modernize-use-std-format)
            snprintf( // NOSONAR S6494: std::format not usable on ESP32
                _buffer.data(), _buffer.size(),
                "%s: %*sPointer: %p\n", name.data(), _indentation * 2, "", pointer);
            OutputBuffer(taskId, Types::ELogLevel::Debug);
        }
    }

    void Log::UInt(
        Types::ETaskId taskId,
        std::string_view name,
        unsigned int value)
    {
        if (Log_ENABLED)
        {
            // NOLINTNEXTLINE(modernize-use-std-format)
            snprintf( // NOSONAR S6494: std::format not usable on ESP32
                _buffer.data(), _buffer.size(), "%s: %ud\n", name.data(), value);
            OutputBuffer(taskId, Types::ELogLevel::Debug);
        }
    }

    void Log::Int(
        Types::ETaskId taskId,
        std::string_view name, int value)
    {
        if (Log_ENABLED)
        {
            // NOLINTNEXTLINE(modernize-use-std-format)
            snprintf( // NOSONAR S6494: std::format not usable on ESP32
                _buffer.data(), _buffer.size(), "%s: %d\n", name.data(), value);
            OutputBuffer(taskId, Types::ELogLevel::Debug);
        }
    }

    void Log::IntAsBits(
        Types::ETaskId taskId,
        std::string_view name,
        int value)
    {
        if (Log_ENABLED)
        {
            // Determine bit width needed
            constexpr int BITS = sizeof(int) * 8;  // 32 bits for int

            char bits[BITS + BITS / 4 + 1] = {};    //  NOSONAR 5945: std::array
            // room for spaces every 4 bits 
            int pos = 0;

            for (int i = BITS - 1; i >= 0; --i)
            {
                bits[pos++] = (value >> i) & 1 ? '1' : '0';
                // Add space after every 4 bits (except at the end)
                if (i % 4 == 0 && i != 0)
                    bits[pos++] = ' ';
            }
            bits[pos] = '\0';

            // NOLINTNEXTLINE(modernize-use-std-format)
            snprintf( // NOSONAR S6494: std::format not usable on ESP32
                _buffer.data(), _buffer.size(), "%.*s: %.*s\n",
                static_cast<int>(_buffer.size() / 3), name.data(),
                static_cast<int>(_buffer.size() / 3), bits);
            OutputBuffer(taskId, Types::ELogLevel::Debug);
        }
    }


    void Log::Char(
        Types::ETaskId taskId,
        std::string_view name,
        char value)
    {
        if (Log_ENABLED)
        {
            snprintf( // NOSONAR S6494 sprintf not on ESP32
                _buffer.data(), _buffer.size(), "%s: %c\n", name.data(), value);
            OutputBuffer(taskId, Types::ELogLevel::Debug);
        }
    }

    void Log::String(
        Types::ETaskId taskId,
        std::string_view name,
        std::string_view value)
    {
        if (Log_ENABLED)
        {
            snprintf( // NOSONAR S6494 sprintf not on ESP32
                _buffer.data(), _buffer.size(), "%s: %s\n", name.data(), value.data());
            OutputBuffer(taskId, Types::ELogLevel::Debug);
        }
    }

    void Log::Text(
        Types::ETaskId taskId,
        std::string_view text,
        Types::ELogLevel logLevel /* = Types::ELogLevel::Debug */)
    {
        if (Log_ENABLED)
        {
            snprintf( // NOSONAR S6494 sprintf not on ESP32
                _buffer.data(), _buffer.size(), "%s\n", text.data());
            OutputBuffer(taskId, logLevel);
        }
    }

    void Log::OutputBuffer(
        [[maybe_unused]] Types::ETaskId taskId,
        [[maybe_unused]] Types::ELogLevel logLevel)
    {
        if (Log_ENABLED)
        {
            auto timeStamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                _timeUtilities.GetCurrentTimeInUs());
            _diagnosticsQueueWriter->SendLogEntry(taskId, timeStamp, logLevel, _buffer.data());

#ifdef _MSC_VER
            OutputDebugStringA(_buffer.data());
#endif
        }
    }
}
