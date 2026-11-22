// @file Log.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "ILog.hpp"
#include "../../M30_Messages/Types.hpp"
#include <array>

namespace M90::Time
{
    class ITimeUtilities;
}

class DiagnosticsQueue;
class DiagnosticsQueueWriter;

namespace M90::Log
{
    class Log : public ILog
    {
    public:
        explicit Log(
            M90::Time::ITimeUtilities& timeUtilities);

        virtual ~Log() = default;

        uint32_t GetLogLevels() override;

        void SetLogLevels(
            uint32_t logLevels) override;

        void SetDiagnostics(
            DiagnosticsQueue& diagnosticsQueue,
            DiagnosticsQueueWriter& diagnosticsQueueWriter) override;

        void Entry(
            Types::ETaskId taskId,
            std::string_view name) override;

        void Exit(
            Types::ETaskId taskId,
            std::string_view name) override;

        void Pointer(
            Types::ETaskId taskId,
            std::string_view name,
            const void* pointer) override;

        void UInt(
            Types::ETaskId taskId,
            std::string_view name,
            unsigned int value) override;

        void Int(
            Types::ETaskId taskId,
            std::string_view name,
            int value) override;

        void IntAsBits(
            Types::ETaskId taskId,
            std::string_view name,
            int value) override;

        void Char(
            Types::ETaskId taskId,
            std::string_view name,
            char value) override;

        void String(
            Types::ETaskId taskId,
            std::string_view name,
            std::string_view value) override;

        /// @inheritdoc
        void Text(
            Types::ETaskId taskId,
            std::string_view text,
            Types::ELogLevel logLevel) override;

    private:
        static constexpr uint8_t BUFFER_SIZE = 255;

        void OutputBuffer(
            Types::ETaskId taskId,
            Types::ELogLevel logLevel);

        uint32_t _logLevels;

        DiagnosticsQueue* _diagnosticsQueue;
        
        DiagnosticsQueueWriter* _diagnosticsQueueWriter;

        std::array<char, BUFFER_SIZE> _buffer;
        
        uint8_t _indentation;

        M90::Time::ITimeUtilities& _timeUtilities;
    };
}
