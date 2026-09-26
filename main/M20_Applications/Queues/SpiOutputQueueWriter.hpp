#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <string>

class SpiOutputQueue;
class ApplicationsManager;

class SpiOutputQueueWriter : public QueueProcessor
{
public:
    SpiOutputQueueWriter(
        SpiOutputQueue& spiOutputQueue, 
        ApplicationsManager& applicationsManager);

    ~SpiOutputQueueWriter() = default;
    
    //TODOSPI
    // void SendLed(
    //     Types::ELedId, 
    //     bool state);

private:
    SpiOutputQueue& GetSpiOutputQueue();

    ApplicationsManager& _applicationsManager;  
};
