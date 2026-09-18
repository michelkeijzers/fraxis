#pragma once

#include "../M80_Services/RtosQueue/RtosQueue.hpp"

class Queue
{
public:
    Queue();
    virtual ~Queue() = default;

    void SetRtosQueue(
        RtosQueue& rtosQueue);
    RtosQueue& GetRtosQueue();

private:
    RtosQueue* _rtosQueue;
};
