#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/Spi/SpiInputQueue.hpp"
#include <cstdint>
#include <string>

class spiInputQueue;
class MicroSdCard;

class SpiInputQueueWriter : public QueueProcessor
{
public:
    SpiInputQueueWriter(
        SpiInputQueue& spiInputQueue, 
        MicroSdCard& microSdCard);

    SpiInputQueueWriter(const SpiInputQueueWriter&) = delete;
    SpiInputQueueWriter& operator=(const SpiInputQueueWriter&) = delete;
    SpiInputQueueWriter(SpiInputQueueWriter&&) = delete;
    SpiInputQueueWriter& operator=(SpiInputQueueWriter&&) = delete;

    ~SpiInputQueueWriter() override = default;

    // NOSONAR TODO void SendLoadedDataMessage();
    
    void SendWrite();

private:
    SpiInputQueue& GetSpiInputQueue();

    MicroSdCard& _microSdCard;
};
