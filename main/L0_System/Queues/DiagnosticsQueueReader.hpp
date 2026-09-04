#pragma once

#include "../../L3_Messages/QueueProcessor.hpp"

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
    ~DiagnosticsQueueReader() = default;
    
    bool HandleMessage();

private:
    DiagnosticsQueue& GetDiagnosticsQueue();
    
    WatchDog& _watchDog;
    DiagnosticsManager& _diagnosticsManager;
};
