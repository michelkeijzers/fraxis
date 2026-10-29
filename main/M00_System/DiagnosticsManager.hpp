#pragma once

#include "../M30_Messages/Types.hpp"
#include "../M30_Messages/Diagnostics/DiagnosticsQueue.hpp"
#include <cstdlib>
#include <chrono>
#include <array>

class Context;

class DiagnosticsManager
{
public:
    explicit DiagnosticsManager(
        Context& context);

    DiagnosticsManager(const DiagnosticsManager&) = delete;
    DiagnosticsManager& operator=(const DiagnosticsManager&) = delete;
    DiagnosticsManager(DiagnosticsManager&&) = delete;
    DiagnosticsManager& operator=(DiagnosticsManager&&) = delete;

    virtual ~DiagnosticsManager() = default;

    #pragma pack(push, 1)
    struct TaskDataStruct
    {
        uint8_t  taskId = 0;
        std::chrono::microseconds timeStamp = {};
        uint32_t stackSize = 0;
    };
    #pragma pack(pop)

    void OnTaskData(
        Types::ETaskId taskId = Types::ETaskId::ApplicationsTask, 
        std::chrono::microseconds timeStamp = {}, 
        uint32_t stackSize = 0);

    #pragma pack(push, 1)
    struct LogEntryStruct
    {
        uint8_t  taskId = 0;
        std::chrono::microseconds timeStamp = {};
        uint8_t  logLevel = 0;
        std::array<char, DiagnosticsQueue::MAX_LOG_ENTRY_TEXT_LENGTH> text = {};
    };
    #pragma pack(pop)

    void OnLogEntry(
        Types::ETaskId taskId = Types::ETaskId::ApplicationsTask, 
        std::chrono::microseconds timeStamp = {}, 
        Types::ELogLevel logLevel = Types::ELogLevel::Debug,
        const char* text = nullptr);

private:
    Context& _context;
};
