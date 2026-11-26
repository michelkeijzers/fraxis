#include "I2sTask.hpp"
#include "../../M60_DeviceDrivers/I2s/I2sTaskDeviceDriversDelegate.hpp"
#include "../../M90_Utilities/Log/ILog.hpp"

I2sTask::I2sTask(
    I2sOutputQueueReader& i2sOutputQueueReader,
    M60::I2s::I2sTaskDeviceDriversDelegate& i2sTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
:   
    Task(assert, log),
    _i2sOutputQueueReader(i2sOutputQueueReader),
    _i2sTaskDeviceDriversDelegate(i2sTaskDeviceDriversDelegate)
{
    // No functionality required.
}

void I2sTask::Initialize()
{
    _i2sTaskDeviceDriversDelegate.Initialize();
}

void I2sTask::Run()
{
    GetLog().Entry(Types::ETaskId::I2sTask, "I2sTask::Run()");
    while (true)
    {
        while (_i2sOutputQueueReader.HandleMessage())
        {
            // NOSONAR TODO I2S
        }

        _i2sTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    GetLog().Exit(Types::ETaskId::I2sTask, "I2sTask::Run()");
}

void I2sTask::TaskEntry(
    void* param) // NOSONAR S5008: replace void*
{
    auto* self = static_cast<I2sTask*>(param);
    self->Run();
}
