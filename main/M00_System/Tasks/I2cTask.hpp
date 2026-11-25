#pragma once

#include "../../M40_DomainModels/I2c/I2cOutputQueueReader.hpp"
#include "../../M60_DeviceDrivers/I2c/I2cTaskDeviceDriversDelegate.hpp"
#include "../../M90_Utilities/Task/Task.hpp"

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

namespace M90::Time
{
    class ITimeUtilities;
}

namespace M60::I2c
{
    class Lcd2004DeviceDriver;
    class Mcp23017DeviceDriver;
    class I2cTaskDeviceDriversDelegate;
}

class I2cOutputQueue;
class I2cOutputQueueReader;
class IoPins;
class Mcp23017DeviceModel;
class RtosTask;
class Lcd2004;

class I2cTask : public M90::Task::Task
{
public:
    explicit I2cTask(
        I2cOutputQueueReader& i2cOutputQueueReader,
        M60::I2c::I2cTaskDeviceDriversDelegate& i2cTaskDeviceDriversDelegate,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log);

    I2cTask(
        const I2cTask&) = delete;
    
    I2cTask& operator=(
        const I2cTask&) = delete;
    
    I2cTask(
        I2cTask&&) = delete;
    
    I2cTask& operator=(
        I2cTask&&) = delete;

    ~I2cTask() override = default;

    void Initialize() override;
    
    void Run() override;
    
    static void TaskEntry(
        void* param);

private:
    I2cOutputQueueReader& _i2cOutputQueueReader;

    M60::I2c::I2cTaskDeviceDriversDelegate& _i2cTaskDeviceDriversDelegate;
};
