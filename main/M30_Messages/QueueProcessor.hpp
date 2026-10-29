#pragma once

#include "Queue.hpp"

class QueueProcessor
{
public:
    QueueProcessor();

    QueueProcessor(const QueueProcessor&) = delete;
    QueueProcessor& operator=(const QueueProcessor&) = delete;
    QueueProcessor(QueueProcessor&&) = delete;
    QueueProcessor& operator=(QueueProcessor&&) = delete;

    virtual ~QueueProcessor() = default;

    void SetQueue(
        Queue& queue);
    Queue& GetQueue();

private:
    Queue* _queue;
};
