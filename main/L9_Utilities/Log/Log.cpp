#include "Log.hpp"
#include "../../L0_System/Queues/DiagnosticsQueueWriter.hpp"
#include "../../L3_Messages/Types.hpp"
#include "../../L9_Utilities/Time/TimeUtilities.hpp"
#include <cstdio>
#ifndef ESP_PLATFORM
#include <Windows.h>
#endif

static constexpr bool Log_ENABLED = true; // NOSONAR: needs to before the incude

/* static */ DiagnosticsQueue* Log::_diagnosticsQueue = nullptr;
/* static */ DiagnosticsQueueWriter* Log::_diagnosticsQueueWriter = nullptr;
/* static */ char Log::_buf[256]; // NOSONAR: string is slower
/* static */ uint8_t Log::_indentation = 0;


void Log::Initialize(
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
        snprintf(_buf, sizeof(_buf), "%*s>%s\n", _indentation * 2, "", name.data());
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
        snprintf(_buf, sizeof(_buf), "%*s<%s\n", _indentation * 2, "", name.data());
        OutputBuffer(taskId, Types::ELogLevel::Debug);
    }
}

void Log::Pointer(
    Types::ETaskId taskId,
    std::string_view name, const void* pointer) // NOSONAR: void* to be flexible
{
    if (Log_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %*sPointer: %p\n", name.data(), _indentation * 2, "", pointer);
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
        snprintf(_buf, sizeof(_buf), "%s: %ud\n", name.data(), value);
        OutputBuffer(taskId, Types::ELogLevel::Debug);
    }
}

void Log::Int(
    Types::ETaskId taskId,
    std::string_view name, int value)
{
    if (Log_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s: %d\n", name.data(), value);
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

        char bits[BITS + BITS / 4 + 1] = {};   // room for spaces every 4 bits // NOSONAR: ESP32 prefers char
        int pos = 0;

        for (int i = BITS - 1; i >= 0; --i)
        {
            bits[pos++] = (value >> i) & 1 ? '1' : '0';
            // Add space after every 4 bits (except at the end)
            if (i % 4 == 0 && i != 0)
                bits[pos++] = ' ';
        }
        bits[pos] = '\0';

        snprintf(_buf, sizeof(_buf), "%s: %s\n", name.data(), bits);
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
        snprintf(_buf, sizeof(_buf), "%s: %c\n", name.data(), value);
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
        snprintf(_buf, sizeof(_buf), "%s: %s\n", name.data(), value.data());
        OutputBuffer(taskId, Types::ELogLevel::Debug);
    }
}

void Log::Text(
    Types::ETaskId taskId,
    std::string_view text,
    Types::ELogLevel logLevel /* = Types::ELogLevel::Debug */ )
{
    if (Log_ENABLED)
    {
        snprintf(_buf, sizeof(_buf), "%s\n", text.data());
        OutputBuffer(taskId, logLevel);
    }
}

void Log::OutputBuffer(
    Types::ETaskId taskId,
    Types::ELogLevel logLevel)
{
    if (Log_ENABLED)
    {
#ifdef ESP_PLATFORM
        uint64_t timeStamp = TimeUtilities::GetCurrentTimeInUs();
        _diagnosticsQueueWriter->SendLogEntry(taskId, timeStamp, logLevel, _buf);
#else
        OutputDebugStringA(_buf);
#endif
    }
}
