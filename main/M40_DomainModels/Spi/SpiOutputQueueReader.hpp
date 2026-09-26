#pragma once

#include "../../M30_Messages/Types.hpp"
#include "../../M30_Messages/QueueProcessor.hpp"

class SpiOutputQueue;
class MicroSdCard;

class SpiOutputQueueReader : public QueueProcessor
{
public:
    SpiOutputQueueReader(
        SpiOutputQueue& spiOutputQueue,  
        MicroSdCard& microSdCard);
    ~SpiOutputQueueReader() = default;
    
    bool HandleMessage();

private:
    SpiOutputQueue& GetSpiOutputQueue();

    MicroSdCard& _microSdCard;
};
