#pragma once

#include "../../M30_Messages/Types.hpp"
#include <string>
#include <array>

class DiagnosticsQueue;
class DiagnosticsQueueWriter;

class Log
{
public:
    static uint32_t GetLogLevels();

    static void SetLogLevels(
        uint32_t logLevels);
        
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
    /// @param logLevel The log level of the message. Text is also used for asserts where Critical
    /// will be the log level. To make it easier for debug text logs, the default log level is 
    /// debug.
    static void Text(
        Types::ETaskId taskId,
        std::string_view text,
        Types::ELogLevel logLevel = Types::ELogLevel::Debug);
    
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
