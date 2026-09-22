#pragma once

#include "../../M30_Messages/NvsQueue.hpp"
#include "../../M30_Messages/QueueProcessor.hpp"

class Nvs;

class NvsQueueReader : public QueueProcessor
{
public:
    NvsQueueReader(
        NvsQueue& nvsQueue,
        Nvs& nvs);
    ~NvsQueueReader() = default;

    bool HandleMessage();

private:
    NvsQueue& GetNvsQueue();

    NvsQueue& _nvsQueue;
    Nvs& _nvs;
};
