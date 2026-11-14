#pragma once

namespace M81::RtosQueue
{
    class IRtosQueue;
}

class Queue
{
public:
    Queue();

    Queue(
        const Queue&) = delete;
    
    Queue& operator=(
        const Queue&) = delete;
    
    Queue(
        Queue&&) = delete;
    
    Queue& operator=(
        Queue&&) = delete;

    virtual ~Queue() = default;

    void SetRtosQueue(
        M81::RtosQueue::IRtosQueue& rtosQueue);

    M81::RtosQueue::IRtosQueue& GetRtosQueue();

private:
    M81::RtosQueue::IRtosQueue* _rtosQueue;
};
