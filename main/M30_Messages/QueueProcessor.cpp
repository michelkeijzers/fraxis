#include "QueueProcessor.hpp"
#include "../M90_Utilities/Assert/IAssert.hpp" 

QueueProcessor::QueueProcessor(
M90::Assert::IAssert& assert)
:
    _assert(assert),
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
