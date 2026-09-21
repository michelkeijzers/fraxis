#include "NvsTask.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M90_Utilities/Log/Log.hpp"

NvsTask::NvsTask(Context& context) 
:   Task(), 
    _context(context),
    _nvsQueue(_context.GetQueues().GetNvsQueue()),
    _nvsQueueReader(_nvsQueue, _context.GetServices().GetNvs()),
    _nvsQueueWriter(_nvsQueue, _context.GetServices().GetNvs())
{
}

void NvsTask::Initialize()
{
}

void NvsTask::Run()
{
    Log::Entry(Types::ETaskId::NvsTask, "NvsTask::Run()");
    while (true)
    {
        while (_nvsQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        while (_nvsQueueWriter.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        GetRtosTask().DelayTask(1);
    }
    Log::Exit(Types::ETaskId::NvsTask, "NvsTask::Run()");
}

/* static */ void NvsTask::TaskEntry(
    void* param) // NOSONAR: RTOS task entry must use void* by design
{
    auto* self = static_cast<NvsTask*>(param);
    self->Run();
}
