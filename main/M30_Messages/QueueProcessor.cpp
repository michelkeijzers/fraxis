#include "QueueProcessor.hpp"
#include "../M90_Utilities/Assert/IAssert.hpp" 

QueueProcessor::QueueProcessor(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities)
:
    _assert(assert),
    _log(log),
    _stringUtilities(stringUtilities),
    _queue(nullptr)
{}

void QueueProcessor::SetQueue(
    Queue& queue)
{
    _queue = &queue;
}

Queue& QueueProcessor::GetQueue()
{
    return *_queue;
}

M90::Assert::IAssert& QueueProcessor::GetAssert() const
{
    return _assert;
}

M90::Log::ILog& QueueProcessor::GetLog() const
{
    return _log;
}

M90::String::IStringUtilities& QueueProcessor::GetStringUtilities() const
{
    return _stringUtilities;
}
