#include "PassiveBuzzerTask.hpp"
#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzerQueueReader.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"

#include "../../M90_Utilities/Log/Log.hpp"

PassiveBuzzerTask::PassiveBuzzerTask(
    PassiveBuzzerQueueReader& passiveBuzzerQueueReader,
    M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate& 
        passiveBuzzerTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
:   
    Task(assert, log),
    _passiveBuzzerQueueReader(passiveBuzzerQueueReader),
    _passiveBuzzerTaskDeviceDriversDelegate(passiveBuzzerTaskDeviceDriversDelegate)
{
    // No functionality required.
}

void PassiveBuzzerTask::Initialize()
{
    _passiveBuzzerTaskDeviceDriversDelegate.Initialize();
}

void PassiveBuzzerTask::Run()
{
    GetLog().Entry(Types::ETaskId::PassiveBuzzerTask, "PassiveBuzzerTask::Run()");
    while (true)
    {
        while (_passiveBuzzerQueueReader.HandleMessage())
        {
            // Endless loop.
        }

        _passiveBuzzerTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    GetLog().Exit(Types::ETaskId::PassiveBuzzerTask, "PassiveBuzzerTask::Run()");
}

void PassiveBuzzerTask::TaskEntry(
    void* param) // NOSONAR S5008: replace void*
{
    auto* self = static_cast<PassiveBuzzerTask*>(param);
    self->Run();
}
