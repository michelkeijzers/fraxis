#pragma once

namespace M81::RtosQueue
{
    class RtosQueue;
}

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
        M81::RtosQueue::RtosQueue& rtosQueue);
    M81::RtosQueue::RtosQueue& GetRtosQueue();

private:
    M81::RtosQueue::RtosQueue* _rtosQueue;
};
