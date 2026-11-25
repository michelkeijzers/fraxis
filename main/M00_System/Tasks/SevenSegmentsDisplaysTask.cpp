#include "SevenSegmentsDisplaysTask.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

SevenSegmentsDisplaysTask::SevenSegmentsDisplaysTask(
    Context& context,
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities,
    M90::Time::ITimeUtilities& timeUtilities)
:
    Task(assert, log),
    _context(context), 
    _assert(assert),
    _tm1637CentralPanel(context.GetDomainModels().GetTm1637CentralPanel()),
    _tm1637Player1(context.GetDomainModels().GetTm1637Player1()),
    _tm1637Player2(context.GetDomainModels().GetTm1637Player2()),
    _sevenSegmentsDisplaysQueue(_context.GetQueues().GetSevenSegmentsDisplaysQueue()),

    _sevenSegmentsDisplaysQueueReader(
        assert, 
        log,
        stringUtilities,
        _sevenSegmentsDisplaysQueue,
        _tm1637CentralPanel, 
        _tm1637Player1, 
        _tm1637Player2),
    
    _sevenSegmentsDisplaysTaskDeviceDriversDelegate(
        tm1637DeviceDriverCentralPanel,
        tm1637DeviceDriverPlayer1,
        tm1637DeviceDriverPlayer2,
        assert,
        log,
        timeUtilities)
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
