#pragma once

#include "../M81_RtosServices/RtosQueue/RtosQueue.hpp"

class Queue
{
public:
    Queue();

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator=(Queue&&) = delete;

    virtual ~Queue() = default;

    void SetRtosQueue(
        RtosQueue& rtosQueue);
    RtosQueue& GetRtosQueue();

private:
    RtosQueue* _rtosQueue;
};
