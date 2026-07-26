#pragma once

#include "../L4_DomainModels/I2c/OutputQueueReader.hpp"
#include "../L6_DeviceDrivers/I2cTaskDeviceDriversDelegate.hpp"
#include "../L9_Utils/Task/Task.hpp"

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

    I2cTaskDeviceDriversDelegate _i2cTaskDeviceDriversDelegate;
};
