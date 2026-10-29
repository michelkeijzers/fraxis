#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"

class DiagnosticsQueue;
class WatchDog;
class DiagnosticsManager;

class DiagnosticsQueueReader : public QueueProcessor
{
public:
    DiagnosticsQueueReader(
        DiagnosticsQueue& diagnosticsQueue, 
        WatchDog& watchDog, 
        DiagnosticsManager& diagnosticsManager);

    DiagnosticsQueueReader(const DiagnosticsQueueReader&) = delete;
    DiagnosticsQueueReader& operator=(const DiagnosticsQueueReader&) = delete;
    DiagnosticsQueueReader(DiagnosticsQueueReader&&) = delete;
    DiagnosticsQueueReader& operator=(DiagnosticsQueueReader&&) = delete;

    ~DiagnosticsQueueReader() override = default;
    
    bool HandleMessage();

private:
    DiagnosticsQueue& GetDiagnosticsQueue();
    
    WatchDog& _watchDog;
    DiagnosticsManager& _diagnosticsManager;
};
