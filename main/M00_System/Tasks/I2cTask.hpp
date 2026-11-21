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
}

class Context;
class RtosTask;
class Lcd2004;
class IoPins;
class I2cOutputQueue;

class I2cTask : public M90::Task::Task
{
public:
    explicit I2cTask(
        Context& context,
        M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver,
        M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        M90::Time::ITimeUtilities& timeUtilities);

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
    Context& _context;

    M90::Assert::IAssert& _assert;

    Lcd2004& _lcd2004;
    
    IoPins& _ioPins;
    
    I2cOutputQueue& _i2cOutputQueue;
    
    I2cOutputQueueReader _i2cOutputQueueReader;

    M60::I2c::I2cTaskDeviceDriversDelegate _i2cTaskDeviceDriversDelegate;
};
