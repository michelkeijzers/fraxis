#include "LedStripsTask.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../M90_Utilities/Log/Log.hpp"

LedStripsTask::LedStripsTask(Context& context) 
:
    _context(context), 
    _ledStrips(_context.GetDomainModels().GetLedStrips()),
    _ledStripsQueue(_context.GetQueues().GetLedStripsQueue()), 
    _ledStripsQueueReader(_ledStripsQueue, _ledStrips),
    _ws28xxTaskDeviceDriversDelegate(context)
{
}

void LedStripsTask::Initialize()
{
    _ws28xxTaskDeviceDriversDelegate.Initialize();
}

void LedStripsTask::Run()
{
    M90::Log::Log::Entry(Types::ETaskId::LedStripsTask, "LedStripsTask::Run()");
    while (true)
    {
        while (_ledStripsQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _ws28xxTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    M90::Log::Log::Exit(Types::ETaskId::LedStripsTask, "LedStripsTask::Run()");
}

/* static */ void LedStripsTask::TaskEntry(
    void* param) // NOSONAR: ESP32 expects void*
{
    auto* self = static_cast<LedStripsTask*>(param);
    self->Run();
}
