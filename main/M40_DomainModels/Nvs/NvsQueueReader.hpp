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

private:
    bool ProcessMessage(
        void* message) override;

    NvsQueue& _nvsQueue;
    Nvs& _nvs;
};
