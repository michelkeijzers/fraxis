#pragma once

#include "../M30_Messages/Types.hpp"
#include "../M30_Messages/DiagnosticsQueue.hpp"
#include <cstdlib>
#include <chrono>

class Context;

class DiagnosticsManager
{
public:
    DiagnosticsManager(Context& context);
    virtual ~DiagnosticsManager() = default;

    #pragma pack(push, 1)
    struct TaskDataStruct
    {
        uint8_t  taskId;
        std::chrono::microseconds timeStamp;
        uint32_t stackSize;
    };
    #pragma pack(pop)

    void OnTaskData(
        Types::ETaskId taskId, 
        std::chrono::microseconds timeStamp, 
        uint32_t stackSize);

    #pragma pack(push, 1)
    struct LogEntryStruct
    {
        uint8_t  taskId;
        std::chrono::microseconds timeStamp;
        uint8_t  logLevel;
        char     text[DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH];
    };
    #pragma pack(pop)

    void OnLogEntry(
        Types::ETaskId taskId, 
        std::chrono::microseconds timeStamp, 
        Types::ELogLevel logLevel,
        const char* text);

private:
    Context& _context;
};
