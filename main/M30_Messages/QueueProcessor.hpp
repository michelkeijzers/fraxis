#pragma once

#include "Queue.hpp"

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

namespace M90::String
{
    class IStringUtilities;
}

class QueueProcessor
{
public:
    QueueProcessor(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities);

    QueueProcessor(
        const QueueProcessor&) = delete;
    
    QueueProcessor& operator=(
        const QueueProcessor&) = delete;
    
    QueueProcessor(
        QueueProcessor&&) = delete;
    
    QueueProcessor& operator=(
        QueueProcessor&&) = delete;

    virtual ~QueueProcessor() = default;

    void SetQueue(
        Queue& queue);

    Queue& GetQueue();

    M90::Assert::IAssert& GetAssert() const;

    M90::Log::ILog& GetLog() const;

    M90::String::IStringUtilities& GetStringUtilities() const;

private:
    M90::Assert::IAssert& _assert;

    M90::Log::ILog& _log;

    M90::String::IStringUtilities& _stringUtilities;

    Queue* _queue;
};
