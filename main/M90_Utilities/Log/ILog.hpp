// @file ILog.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../../M30_Messages/Types.hpp"
#include <string>
#include <array>

class DiagnosticsQueue;
class DiagnosticsQueueWriter;

namespace M90::Log
{
    class ILog
    {
    public:
        virtual ~ILog() = default;

        virtual uint32_t GetLogLevels() = 0;

        virtual void SetLogLevels(
            uint32_t logLevels) = 0;

        virtual void SetDiagnostics(
            DiagnosticsQueue& diagnosticsQueue,
            DiagnosticsQueueWriter& diagnosticsQueueWriter) = 0;

        virtual void Entry(
            Types::ETaskId taskId,
            std::string_view name) = 0;

        virtual void Exit(
            Types::ETaskId taskId,
            std::string_view name) = 0;

        virtual void Pointer(
            Types::ETaskId taskId,
            std::string_view name,
            const void* pointer) = 0;

        virtual void UInt(
            Types::ETaskId taskId,
            std::string_view name,
            unsigned int value) = 0;

        virtual void Int(
            Types::ETaskId taskId,
            std::string_view name,
            int value) = 0;

        virtual void IntAsBits(
            Types::ETaskId taskId,
            std::string_view name,
            int value) = 0;

        virtual void Char(
            Types::ETaskId taskId,
            std::string_view name,
            char value) = 0;

        virtual void String(
            Types::ETaskId taskId,
            std::string_view name,
            std::string_view value) = 0;

        /// @brief Logs a text message.
        /// @param taskId The task ID from which the log is generated.
        /// @param text The text message to log.
        /// @param logLevel The log level of the message. Text is also used for asserts where 
        /// Critical will be the log level. To make it easier for debug text logs, the default
        /// log level is debug.
        virtual void Text(
            Types::ETaskId taskId,
            std::string_view text,
            Types::ELogLevel logLevel = Types::ELogLevel::Debug) = 0;
    };
}
