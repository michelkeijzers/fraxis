// @file Log.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "ILog.hpp"
#include "../../M30_Messages/Types.hpp"
#include <string>
#include <array>

class DiagnosticsQueue;
class DiagnosticsQueueWriter;

namespace M90::Log
{
    class Log : public ILog
    {
    public:
        uint32_t GetLogLevels() override;

        void SetLogLevels(
            uint32_t logLevels) override;

        void Initialize(
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
        static constexpr uint8_t BUFFER_SIZE = 20;

        static void OutputBuffer(
            Types::ETaskId taskId,
            Types::ELogLevel logLevel);

        static uint32_t _logLevels;

        static DiagnosticsQueue* _diagnosticsQueue;
        
        static DiagnosticsQueueWriter* _diagnosticsQueueWriter;

        static std::array<char, BUFFER_SIZE> _buf;
        
        static uint8_t _indentation;
    };
}
