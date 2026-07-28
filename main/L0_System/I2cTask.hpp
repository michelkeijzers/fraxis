#pragma once

#include "../L4_DomainModels/I2c/I2cOutputQueueReader.hpp"
#include "../L6_DeviceDrivers/I2cTaskDeviceDriversDelegate.hpp"
#include "../L9_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class IoPins;
class Displays;
class I2cOutputQueue;

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

    I2cOutputQueue& _i2cOutputQueue;
    I2cOutputQueueReader _i2cOutputQueueReader;

    I2cTaskDeviceDriversDelegate _i2cTaskDeviceDriversDelegate;
};
