#pragma once

#include "../../M30_Messages/NvsQueue.hpp"
#include "../../M30_Messages/QueueProcessor.hpp"

class Nvs;

class NvsQueueWriter : public QueueProcessor
{
public:
    NvsQueueWriter(
        NvsQueue& nvsQueue,
        Nvs& nvs);
    ~NvsQueueWriter() = default;

private:
    // TODONVS: Send message commands

    NvsQueue& _nvsQueue;
    Nvs& _nvs;
};
