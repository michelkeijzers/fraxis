#pragma once

#include "Queue.hpp"

namespace M90::Assert
{
    class IAssert;
}

class QueueProcessor
{
public:
    QueueProcessor(
        M90::Assert::IAssert& assert);

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

protected:
    M90::Assert::IAssert& GetAssert() const;

private:
    M90::Assert::IAssert& _assert;

    Queue* _queue;
};
