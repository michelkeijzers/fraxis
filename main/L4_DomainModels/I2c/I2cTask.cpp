#include "I2cTask.hpp"
#include "Displays/Displays.hpp"
#include "../../L1_Composition/Context/Context.hpp"

I2cTask::I2cTask(Context& context) 
:   Task(), _context(context), 
    _ioPins(context.GetDomainModels().GetIoPins()),
    _displays(context.GetDomainModels().GetDisplays()),
    _outputQueue(_context.GetQueues().GetOutputQueue()),
    _outputQueueReader(_outputQueue, _ioPins, _displays),
    _i2cTaskDelegateDeviceModels(context)
{
}


I2cTask::~I2cTask() 
{
}

void I2cTask::Initialize()
{
}

void I2cTask::Run()
{
    while (true)
    {
        while (_outputQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _i2cTaskDelegateDeviceModels.Run();
        _rtosTask->DelayTask(1);
    }
}

/* static */ void I2cTask::TaskEntry(void* param)
{
    auto* self = static_cast<I2cTask*>(param);
    self->Run();
}
