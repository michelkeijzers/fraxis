#pragma once

#include "Task.hpp"
#include "ApplicationsManager.hpp"

#include "Queues/InputQueueReader.hpp"
#include "Queues/OutputQueueWriter.hpp"
#include "Queues/LedStripsQueueWriter.hpp"
#include "Queues/QueueWriters.hpp"
#include "../L3_Messages/LedStripsQueue.hpp"
#include "../L3_Messages/InputQueue.hpp"
#include "../L3_Messages/OutputQueue.hpp"

#include "../L8_Services/RtosTask/RtosTask.hpp"

class Context;
class ApplicationsManager;
class LedStripsQueue;
class InputQueue;
class OutputQueue;
class InputQueueReader;
class OutputQueueWriter;
class LedStripsQueueWriter;

class ApplicationsTask : public Task
{
public:
    ApplicationsTask(Context& context);
    ~ApplicationsTask();

    void Initialize() override;
    void Run() override;
    static void TaskEntry(void* param);

private:
    Context& _context;
    ApplicationsManager _applicationsManager;

    LedStripsQueue& _ledStripsQueue;
    InputQueue& _inputQueue;
    OutputQueue& _outputQueue;

    InputQueueReader _inputQueueReader;
    OutputQueueWriter _outputQueueWriter;
    LedStripsQueueWriter _ledStripsQueueWriter;
    QueueWriters _queueWriters;
};
