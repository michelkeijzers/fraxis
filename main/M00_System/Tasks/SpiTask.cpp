#include "SpiTask.hpp"

#include "../../M90_Utilities/Log/ILog.hpp"

SpiTask::SpiTask(
    SpiOutputQueueReader& spiOutputQueueReader,
    M60::Spi::SpiTaskDeviceDriversDelegate& spiTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
:   
    Task(assert, log),
    _spiOutputQueueReader(spiOutputQueueReader),
    _spiTaskDeviceDriversDelegate(spiTaskDeviceDriversDelegate)
{
    // No functionality required.
}

void SpiTask::Initialize()
{
    _spiTaskDeviceDriversDelegate.Initialize();
}

void SpiTask::Run()
{
    GetLog().Entry(Types::ETaskId::SpiTask, "SpiTask::Run()");
    while (true)
    {
        while (_spiOutputQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _spiTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    GetLog().Exit(Types::ETaskId::SpiTask, "SpiTask::Run()");
}

/* static */ void SpiTask::TaskEntry(
    void* param) // NOSONAR: RTOS task entry must use void* by design
{
    auto* self = static_cast<SpiTask*>(param);
    self->Run();
}
