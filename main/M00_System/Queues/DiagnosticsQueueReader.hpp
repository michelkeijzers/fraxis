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
        DiagnosticsManager& diagnosticsManager,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);

    DiagnosticsQueueReader(
        const DiagnosticsQueueReader&) = delete;
    
    DiagnosticsQueueReader& operator=(
        const DiagnosticsQueueReader&) = delete;
    
    DiagnosticsQueueReader(
        DiagnosticsQueueReader&&) = delete;
    
    DiagnosticsQueueReader& operator=(
        DiagnosticsQueueReader&&) = delete;

    ~DiagnosticsQueueReader() override = default;
    
    bool HandleMessage();

private:
    DiagnosticsQueue& GetDiagnosticsQueue();
    
    WatchDog& _watchDog;

    DiagnosticsManager& _diagnosticsManager;
};
