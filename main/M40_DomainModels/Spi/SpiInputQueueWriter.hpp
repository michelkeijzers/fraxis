#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/SpiInputQueue.hpp"
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
    ~SpiInputQueueWriter();

    void SendWrite(); // TODOSPI: arguments

private:
    SpiInputQueue& GetSpiInputQueue();

    MicroSdCard& _microSdCard;
};
