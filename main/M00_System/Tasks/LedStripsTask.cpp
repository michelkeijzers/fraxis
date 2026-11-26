#include "LedStripsTask.hpp"

#include "../../M90_Utilities/Log/ILog.hpp"

LedStripsTask::LedStripsTask(
    LedStripsQueueReader& ledStripsQueueReader,
    M60::Ws28xx::Ws28xxTaskDeviceDriversDelegate& ws28xxTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
:
    Task(assert, log),
    _ledStripsQueueReader(ledStripsQueueReader),
    _ws28xxTaskDeviceDriversDelegate(ws28xxTaskDeviceDriversDelegate)
{
    // No functionality required.
}

void LedStripsTask::Initialize()
{
    _ws28xxTaskDeviceDriversDelegate.Initialize();
}

void LedStripsTask::Run()
{
    GetLog().Entry(Types::ETaskId::LedStripsTask, "LedStripsTask::Run()");
    while (true)
    {
        while (_ledStripsQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _ws28xxTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    GetLog().Exit(Types::ETaskId::LedStripsTask, "LedStripsTask::Run()");
}

/* static */ void LedStripsTask::TaskEntry(
    void* param) // NOSONAR: ESP32 expects void*
{
    auto* self = static_cast<LedStripsTask*>(param);
    self->Run();
}
