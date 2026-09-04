#pragma once

#include "../../L3_Messages/Types.hpp"
#include <string>

class DiagnosticsQueue;
class DiagnosticsQueueWriter;

class Log
{
public:
    static void Initialize(
        DiagnosticsQueue& diagnosticsQueue,
        DiagnosticsQueueWriter& diagnosticsQueueWriter);

    static void Entry(
        Types::ETaskId taskId,
        std::string_view name);

    static void Exit(
        Types::ETaskId taskId,
        std::string_view name);

    static void Pointer(
        Types::ETaskId taskId,
        std::string_view name, 
        const void* pointer);

    static void UInt(
        Types::ETaskId taskId,
        std::string_view name, 
        unsigned int value);

    static void Int(
        Types::ETaskId taskId,
        std::string_view name, 
        int value);

    static void IntAsBits(
        Types::ETaskId taskId,
        std::string_view name, 
        int value);

    static void Char(
        Types::ETaskId taskId,
        std::string_view name, 
        char value);

    static void String(
        Types::ETaskId taskId,
        std::string_view name, 
        std::string_view value);

    /// @brief Logs a text message.
    /// @param taskId The task ID from which the log is generated.
    /// @param text The text message to log.
    /// @param logLevel The log level of the message. Text is also used for asserts where Critical will be the log
    /// level. To make it easier for debug text logs, the default log level is debug.
    static void Text(
        Types::ETaskId taskId,
        std::string_view text,
        Types::ELogLevel logLevel = Types::ELogLevel::Debug);
    
private:
    static DiagnosticsQueue* _diagnosticsQueue;
    static DiagnosticsQueueWriter* _diagnosticsQueueWriter;
    static void OutputBuffer(
        Types::ETaskId taskId,
        Types::ELogLevel logLevel);

    static char _buf[256];
    static uint8_t _indentation;
};
