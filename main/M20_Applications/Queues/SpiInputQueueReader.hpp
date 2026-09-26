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
    ~SpiInputQueueReader() = default;
    
    bool HandleMessage();

private:
    SpiInputQueue& GetSpiInputQueue();
    
    ApplicationsManager& _applicationsManager;
};
