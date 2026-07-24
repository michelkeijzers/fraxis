#pragma once

#include "../L8_Services/RtosQueue/RtosQueue.hpp"

class Queue
{
public:
    Queue();
    virtual ~Queue();

    void SetRtosQueue(RtosQueue& rtosQueue);
    RtosQueue& GetRtosQueue() { return *_rtosQueue; }

protected:
    RtosQueue* _rtosQueue;
};
