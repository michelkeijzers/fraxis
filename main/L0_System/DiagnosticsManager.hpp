#pragma once

#include "../L3_Messages/Types.hpp"
#include "../L3_Messages/DiagnosticsQueue.hpp"
#include <cstdlib>

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
        uint64_t timeStamp;
        uint64_t stackSize;
    };
    #pragma pack(pop)

    void OnTaskData(
        Types::ETaskId taskId, 
        uint64_t timeStamp, 
        uint64_t stackSize);

    #pragma pack(push, 1)
    struct LogEntryStruct
    {
        uint8_t  taskId;
        uint64_t timeStamp;
        uint8_t  logLevel;
        char     text[DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH];
    };
    #pragma pack(pop)

    void OnLogEntry(
        Types::ETaskId taskId, 
        uint64_t timeStamp, 
        Types::ELogLevel logLevel,
        const char* text);

private:
    Context& _context;
};
