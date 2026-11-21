#include "I2sTask.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../M90_Utilities/Log/Log.hpp"

I2sTask::I2sTask(
    Context& context,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities)
:   
    Task(log),
    _context(context),
    _i2sMicrophone(context.GetDomainModels().GetI2sMicrophone()),
    _i2sDac(context.GetDomainModels().GetI2sDac()),
    _passiveBuzzer(context.GetDomainModels().GetPassiveBuzzer()),
    _i2sOutputQueue(_context.GetQueues().GetI2sOutputQueue()),
    _i2sOutputQueueReader(assert, stringUtilities, _i2sOutputQueue, _i2sDac, _passiveBuzzer),
    _i2sTaskDeviceDriversDelegate(context)
{
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
