#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"

class SpiInputQueue;
class ApplicationsManager;

namespace M90::Log
{
    class ILog;
}

class SpiInputQueueReader : public QueueProcessor
{
public:
    SpiInputQueueReader(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        SpiInputQueue& spiInputQueue, 
        ApplicationsManager& applicationsManager);

    SpiInputQueueReader(
        const SpiInputQueueReader&) = delete;
    
    SpiInputQueueReader& operator=(
        const SpiInputQueueReader&) = delete;
    
    SpiInputQueueReader(
        SpiInputQueueReader&&) = delete;
    
    SpiInputQueueReader& operator=(
        SpiInputQueueReader&&) = delete;

    ~SpiInputQueueReader() override = default;
    
    bool HandleMessage();

private:
    SpiInputQueue& GetSpiInputQueue();

    ApplicationsManager& _applicationsManager;
};
