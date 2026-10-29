#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M30_Messages/Diagnostics/DiagnosticsQueue.hpp"
#include <cstdint>
#include <string>
#include <chrono>

class DiagnosticsQueue;

class DiagnosticsQueueWriter : public QueueProcessor
{
public:
    explicit DiagnosticsQueueWriter(
        DiagnosticsQueue& diagnosticsQueue);

    DiagnosticsQueueWriter(const DiagnosticsQueueWriter&) = delete;
    DiagnosticsQueueWriter& operator=(const DiagnosticsQueueWriter&) = delete;
    DiagnosticsQueueWriter(DiagnosticsQueueWriter&&) = delete;
    DiagnosticsQueueWriter& operator=(DiagnosticsQueueWriter&&) = delete;

    ~DiagnosticsQueueWriter() override = default;
    
    void SendHeartBeat(
        Types::ETaskId taskId, 
        std::chrono::microseconds timeStamp);

    void SendTaskData(
        Types::ETaskId taskId, 
        std::chrono::microseconds timeStamp,
        uint32_t stackSize);
    
    void SendLogEntry(
        Types::ETaskId taskId, 
        std::chrono::microseconds timeStamp,
        Types::ELogLevel logLevel,
        const char* text);

private:
    DiagnosticsQueue& GetDiagnosticsQueue();
};
