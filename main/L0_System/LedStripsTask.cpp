#include "LedStripsTask.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../L9_Utilities/Log/Log.hpp"

LedStripsTask::LedStripsTask(Context& context) 
:   Task(), 
    _context(context), 
    _ledStrips(_context.GetDomainModels().GetLedStrips()),
    _ledStripsQueue(_context.GetQueues().GetLedStripsQueue()), 
    _ledStripsQueueReader(_ledStripsQueue, _ledStrips),
    _ledStripsTaskDeviceDriversDelegate(context)
{
}

void LedStripsTask::Initialize()
{
    _ledStripsTaskDeviceDriversDelegate.Initialize();
}

void LedStripsTask::Run()
{
    Log::Entry(Types::ETaskId::LedStripsTask, "LedStripsTask::Run()");
    while (true)
    {
        while (_ledStripsQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _ledStripsTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    Log::Exit(Types::ETaskId::LedStripsTask, "LedStripsTask::Run()");
}

/* static */ void LedStripsTask::TaskEntry(
    void* param) // NOSONAR: ESP32 expects void*
{
    auto* self = static_cast<LedStripsTask*>(param);
    self->Run();
}
