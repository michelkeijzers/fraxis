#include "LedStripsTask.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L4_DomainModels/LedStrips/LedStrips.hpp"
#include "../L9_Utilities/Log/Log.hpp"

LedStripsTask::LedStripsTask(Context& context) 
:   Task(), _context(context), 
    _ledStrips(_context.GetDomainModels().GetLedStrips()),
    _ledStripsQueue(_context.GetQueues().GetLedStripsQueue()), 
    _ledStripsQueueReader(_ledStripsQueue, _ledStrips),
    _ledStripsTaskDeviceDriversDelegate(context)
{
}

LedStripsTask::~LedStripsTask() 
{
}

void LedStripsTask::Initialize()
{
    _ledStripsTaskDeviceDriversDelegate.Initialize();
}

void LedStripsTask::Run()
{
    Log::Entry("LedStripsTask::Run()");
    while (true)
    {
        while (_ledStripsQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _ledStripsTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    Log::Exit("LedStripsTask::Run()");
}

/* static */ void LedStripsTask::TaskEntry(void* param)
{
    auto* self = static_cast<LedStripsTask*>(param);
    self->Run();
}
