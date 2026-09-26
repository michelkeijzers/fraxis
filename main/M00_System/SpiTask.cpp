#include "SpiTask.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M90_Utilities/Log/Log.hpp"

SpiTask::SpiTask(Context& context) 
:   Task(), 
    _context(context), 
    _microSdCard(context.GetDomainModels().GetMicroSdCard()),
    _spiOutputQueue(_context.GetQueues().GetSpiOutputQueue()),
    _spiOutputQueueReader(_spiOutputQueue, _microSdCard),
    _spiTaskDeviceDriversDelegate(context)
{
}

void SpiTask::Initialize()
{
    _spiTaskDeviceDriversDelegate.Initialize();
}

void SpiTask::Run()
{
    Log::Entry(Types::ETaskId::SpiTask, "SpiTask::Run()");
    while (true)
    {
        while (_spiOutputQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _spiTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    Log::Exit(Types::ETaskId::SpiTask, "SpiTask::Run()");
}

/* static */ void SpiTask::TaskEntry(
    void* param) // NOSONAR: RTOS task entry must use void* by design
{
    auto* self = static_cast<SpiTask*>(param);
    self->Run();
}
