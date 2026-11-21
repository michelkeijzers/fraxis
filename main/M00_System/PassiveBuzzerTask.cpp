#include "PassiveBuzzerTask.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../M90_Utilities/Log/Log.hpp"

PassiveBuzzerTask::PassiveBuzzerTask(
    Context& context,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities)
:   
    Task(log),
    _context(context),
    _passiveBuzzer(context.GetDomainModels().GetPassiveBuzzer()),
    _passiveBuzzerOutputQueue(_context.GetQueues().GetPassiveBuzzerOutputQueue()),
    _passiveBuzzerOutputQueueReader(assert, stringUtilities, _passiveBuzzerOutputQueue, _passiveBuzzer),
    _passiveBuzzerTaskDeviceDriversDelegate(context)
{
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
        while (_passiveBuzzerOutputQueueReader.HandleMessage())
        {
            // NOSONAR TODO I2S
        }

        _passiveBuzzerTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    GetLog().Exit(Types::ETaskId::I2sTask, "I2sTask::Run()");
}

void PassiveBuzzerTask::TaskEntry(
    void* param) // NOSONAR S5008: replace void*
{
    auto* self = static_cast<PassiveBuzzerTask*>(param);
    self->Run();
}
