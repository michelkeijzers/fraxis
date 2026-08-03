#pragma once

#include "ApplicationsManager.hpp"
#include "Queues/I2cInputQueueReader.hpp"
#include "Queues/I2cOutputQueueWriter.hpp"
#include "Queues/LedStripsQueueWriter.hpp"
#include "Queues/QueueWriters.hpp"
#include "../L8_Services/RtosTask/RtosTask.hpp"
#include "../L9_Utilities/Task/Task.hpp"

class Context;
class ApplicationsManager;
class LedStripsQueue;
class I2cInputQueue;
class I2cOutputQueue;

class ApplicationsTask : public Task
{
public:
    ApplicationsTask(
        Context& context);
    ~ApplicationsTask();

    void Initialize() override;
    void Run() override;
    static void TaskEntry(
        void* param);

private:
    Context& _context;
    ApplicationsManager _applicationsManager;

    I2cInputQueue& _i2cInputQueue;
    I2cInputQueueReader _i2cInputQueueReader;

    I2cOutputQueue& _i2cOutputQueue;
    I2cOutputQueueWriter _i2cOutputQueueWriter;

    LedStripsQueue& _ledStripsQueue;
    LedStripsQueueWriter _ledStripsQueueWriter;

    QueueWriters _queueWriters;
};
