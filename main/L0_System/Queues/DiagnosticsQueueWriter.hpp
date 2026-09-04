#pragma once

#include "../../L3_Messages/QueueProcessor.hpp"
#include "../../L3_Messages/Types.hpp"
#include <cstdint>
#include <string>

class DiagnosticsQueue;

class DiagnosticsQueueWriter : public QueueProcessor
{
public:
    DiagnosticsQueueWriter(
        DiagnosticsQueue& diagnosticsQueue);
    ~DiagnosticsQueueWriter() = default;
    
    void SendHeartBeat(
        Types::ETaskId taskId, 
        uint64_t timeStamp);

    void SendTaskData(
        Types::ETaskId taskId, 
        uint64_t timeStamp,
        uint64_t stackSize);
    
    void SendLogEntry(
        Types::ETaskId taskId, 
        uint64_t timeStamp,
        Types::ELogLevel logLevel,
        const char* text);

private:
    DiagnosticsQueue& GetDiagnosticsQueue();
};
