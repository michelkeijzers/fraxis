#include "../L1_Composition/Context/Context.hpp"
#include "../L1_Composition/Context/DomainModelsContext.hpp"

#include "../L8_Services/Random/Random.hpp"
#include "../L8_Services/RtosQueue/RtosQueue.hpp"
#include "../L9_Utils/Debug/Debug.hpp"
#include "../L9_Utils/Math/MathUtils.hpp"

#include "ApplicationsTask.hpp"
//#include "../Tasks/Messages/Message.hpp" 
#include <cstring>

uint32_t simulatedPlayer1Score = 100000;
uint32_t simulatedPlayer2Score = 0;
uint32_t simulatedTime = 23 * 60 + 59;

ApplicationsTask::ApplicationsTask(Context& context) 
:   Task(), _context(context), _applicationsManager(*this, _context),
    _ledStripsQueue(_context.GetQueues().GetLedStripsQueue()), 
    _inputQueue(_context.GetQueues().GetInputQueue()),
    _outputQueue(_context.GetQueues().GetOutputQueue()),
    _inputQueueReader(_inputQueue, _applicationsManager),
    _outputQueueWriter(_outputQueue, _applicationsManager),
    _ledStripsQueueWriter(_ledStripsQueue, _applicationsManager),
    _queueWriters(_outputQueueWriter, _ledStripsQueueWriter)
{
    _applicationsManager.SetQueueWriters(_queueWriters);
}

ApplicationsTask::~ApplicationsTask() 
{
}

void ApplicationsTask::Initialize()
{
    _applicationsManager.AddApplications();
}

void ApplicationsTask::Run()
{
    while (true)
    {
        // Handle all messages.
        while (_inputQueueReader.HandleMessage())
        {
        }

        _applicationsManager.Run();
        _rtosTask->DelayTask(1);
    }
}

/* static */ void ApplicationsTask::TaskEntry(void* param)
{
    auto* self = static_cast<ApplicationsTask*>(param);
    self->Run();
}
