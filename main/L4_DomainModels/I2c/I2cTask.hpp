#pragma once

#include "../../L2_Applications/Task.hpp"
#include "../../L5_DeviceModels/I2cTaskDelegateDeviceModels.hpp"
#include "OutputQueueReader.hpp"

class Context;
class RtosTask;
class IoPins;
class Displays;
class OutputQueue;

class I2cTask : public Task
{
public:
    I2cTask(Context& context);
    ~I2cTask();

    void Initialize() override;
    void Run() override;
    static void TaskEntry(void* param);

private:
    Context& _context;
    IoPins& _ioPins;
    Displays& _displays;

    OutputQueue& _outputQueue;
    OutputQueueReader _outputQueueReader;

    I2cTaskDelegateDeviceModels _i2cTaskDelegateDeviceModels;
};
