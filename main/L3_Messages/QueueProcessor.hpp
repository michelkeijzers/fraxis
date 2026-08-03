#pragma once

#include "Queue.hpp"

class QueueProcessor
{
public:
    QueueProcessor();
    virtual ~QueueProcessor();

    void SetQueue(
        Queue& queue);
    Queue& GetQueue();

private:
    Queue* _queue;
};
