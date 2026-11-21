#include "I2cTask.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

I2cTask::I2cTask(
    Context& context,
    M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver,
    M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities,
    M90::Time::ITimeUtilities& timeUtilities)
:
    Task(log),
    _context(context), 
    _assert(assert),
    _lcd2004(context.GetDomainModels().GetLcd2004()),
    _ioPins(context.GetDomainModels().GetIoPins()),
    _i2cOutputQueue(_context.GetQueues().GetI2cOutputQueue()),

    _i2cOutputQueueReader(
        assert, 
        stringUtilities,
        _i2cOutputQueue, 
        _lcd2004, 
        _ioPins),
    
    _i2cTaskDeviceDriversDelegate(
        context, 
        lcd2004DeviceDriver,
        mcp23017DeviceDriver, 
        assert,
        stringUtilities,
        timeUtilities)
{
    // No actions required.
}

void I2cTask::Initialize()
{
    _i2cTaskDeviceDriversDelegate.Initialize();
}

void I2cTask::Run()
{
    GetLog().Entry(Types::ETaskId::I2cTask, "I2cTask::Run()");
    while (true)
    {
        while (_i2cOutputQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _i2cTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    GetLog().Exit(Types::ETaskId::I2cTask, "I2cTask::Run()");
}

/* static */ void I2cTask::TaskEntry(
    void* param) // NOSONAR: RTOS task entry must use void* by design
{
    auto* self = static_cast<I2cTask*>(param);
    self->Run();
}
