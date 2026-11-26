#include "SevenSegmentsDisplaysTask.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

SevenSegmentsDisplaysTask::SevenSegmentsDisplaysTask(
    SevenSegmentsDisplaysQueueReader& sevenSegmentsDisplaysQueueReader,
    M60::SevenSegmentsDisplays::SevenSegmentsDisplaysTaskDeviceDriversDelegate& 
        sevenSegmentsDisplaysTaskDeviceDriversDelegate,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
:
    Task(assert, log),
    _sevenSegmentsDisplaysQueueReader(sevenSegmentsDisplaysQueueReader),
    _sevenSegmentsDisplaysTaskDeviceDriversDelegate(sevenSegmentsDisplaysTaskDeviceDriversDelegate)
{
    // No actions required.
}

void SevenSegmentsDisplaysTask::Initialize()
{
    _sevenSegmentsDisplaysTaskDeviceDriversDelegate.Initialize();
}

void SevenSegmentsDisplaysTask::Run()
{
    GetLog().Entry(Types::ETaskId::SevenSegmentsDisplaysTask, "SevenSegmentsDisplaysTask::Run()");
    while (true)
    {
        while (_sevenSegmentsDisplaysQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _sevenSegmentsDisplaysTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    GetLog().Exit(Types::ETaskId::SevenSegmentsDisplaysTask, "SevenSegmentsDisplaysTask::Run()");
}

/* static */ void SevenSegmentsDisplaysTask::TaskEntry(
    void* param) // NOSONAR: RTOS task entry must use void* by design
{
    auto* self = static_cast<SevenSegmentsDisplaysTask*>(param);
    self->Run();
}
