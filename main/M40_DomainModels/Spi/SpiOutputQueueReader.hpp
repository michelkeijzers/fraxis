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

    SpiOutputQueueReader(const SpiOutputQueueReader&) = delete;
    SpiOutputQueueReader& operator=(const SpiOutputQueueReader&) = delete;
    SpiOutputQueueReader(SpiOutputQueueReader&&) = delete;
    SpiOutputQueueReader& operator=(SpiOutputQueueReader&&) = delete;

    ~SpiOutputQueueReader() override = default;
    
    bool HandleMessage();

private:
    SpiOutputQueue& GetSpiOutputQueue();

    MicroSdCard& _microSdCard;
};
