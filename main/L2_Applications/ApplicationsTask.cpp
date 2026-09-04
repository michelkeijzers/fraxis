#include "../L1_Composition/Context/Context.hpp"
#include "../L1_Composition/Context/DomainModelsContext.hpp"
#include "../L8_Services/Random/Random.hpp"
#include "../L8_Services/RtosQueue/RtosQueue.hpp"
#include "../L9_Utilities/Log/Log.hpp"
#include "../L9_Utilities/Math/MathUtilities.hpp"
#include "ApplicationsTask.hpp"
//#include "../Tasks/Messages/Message.hpp" 
#include <cstring>

ApplicationsTask::ApplicationsTask(
    Context& context) 
:   Task(), 
    _context(context), 
    _applicationsManager(_context),
    _i2cInputQueue(_context.GetQueues().GetI2cInputQueue()),
    _i2cInputQueueReader(_i2cInputQueue, _applicationsManager),
    _i2cOutputQueue(_context.GetQueues().GetI2cOutputQueue()),
    _i2cOutputQueueWriter(_i2cOutputQueue, _applicationsManager),
    _ledStripsQueue(_context.GetQueues().GetLedStripsQueue()),
    _ledStripsQueueWriter(_ledStripsQueue, _applicationsManager),
    _queueWriters(_i2cOutputQueueWriter, _ledStripsQueueWriter)
{
    _applicationsManager.SetQueueWriters(_queueWriters);
}

void ApplicationsTask::Initialize()
{
    _applicationsManager.AddApplications();
}

void ApplicationsTask::Run()
{
    while (true)
    {
        while (_i2cInputQueueReader.HandleMessage())
        {
            // Handle all messages.
        }
        _applicationsManager.Run();
        GetRtosTask().DelayTask(1);
    }
    Log::Exit(Types::ETaskId::ApplicationsTask, "ApplicationsTask::Run");
}

/* static */ void ApplicationsTask::TaskEntry(
    void* param) // NOSONAR: ESP32 expects void*
{
    auto& self = *static_cast<ApplicationsTask*>(param);
    self.Run();
}
