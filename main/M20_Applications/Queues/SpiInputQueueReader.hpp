#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"

class SpiInputQueue;
class ApplicationsManager;

class SpiInputQueueReader : public QueueProcessor
{
public:
    SpiInputQueueReader(
        SpiInputQueue& spiInputQueue, 
        ApplicationsManager& applicationsManager);

    SpiInputQueueReader(const SpiInputQueueReader&) = delete;
    SpiInputQueueReader& operator=(const SpiInputQueueReader&) = delete;
    SpiInputQueueReader(SpiInputQueueReader&&) = delete;
    SpiInputQueueReader& operator=(SpiInputQueueReader&&) = delete;

    ~SpiInputQueueReader() override = default;
    
    bool HandleMessage();

private:
    SpiInputQueue& GetSpiInputQueue();

    ApplicationsManager& _applicationsManager;
};
