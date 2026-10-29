#include "QueueProcessor.hpp"

QueueProcessor::QueueProcessor()
:
    _queue(nullptr)
{
}

void QueueProcessor::SetQueue(
    Queue& queue)
{
    _queue = &queue;
}

Queue& QueueProcessor::GetQueue()
{
    return *_queue;
}
