#include "I2cTask.hpp"
#include "../../M40_DomainModels/I2c/I2cOutputQueueReader.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

namespace M60
{
    class I2cTaskDeviceDriversDelegate;
}

I2cTask::I2cTask(
    I2cOutputQueueReader& i2cOutputQueueReader,
    M60::I2c::I2cTaskDeviceDriversDelegate& i2cTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
:
    Task(assert, log),
    _i2cOutputQueueReader(i2cOutputQueueReader),
    _i2cTaskDeviceDriversDelegate(i2cTaskDeviceDriversDelegate)
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
