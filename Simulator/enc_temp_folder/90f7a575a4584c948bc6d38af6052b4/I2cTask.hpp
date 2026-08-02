#pragma once

#include "../L4_DomainModels/I2c/I2cOutputQueueReader.hpp"
#include "../L6_DeviceDrivers/I2cTaskDeviceDriversDelegate.hpp"
#include "../L9_Utilities/Task/Task.hpp"

class Context;
class RtosTask;
class Lcd2004;
class Tm1637;
class IoPins;
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
    Lcd2004& _lcd2004;
    Tm1637& _tm1637CentralPanel;
    Tm1637& _tm1637Player1;
    Tm1637& _tm1637Player2;
    IoPins& _ioPins;
    I2cOutputQueue& _i2cOutputQueue;
    I2cOutputQueueReader _i2cOutputQueueReader;
    I2cTaskDeviceDriversDelegate _i2cTaskDeviceDriversDelegate;
};
