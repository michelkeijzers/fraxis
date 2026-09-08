#pragma once

#include "../L8_Services/RtosQueue/RtosQueue.hpp"

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
