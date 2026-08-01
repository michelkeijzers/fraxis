#include "I2cTask.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L4_DomainModels/I2c/Displays/Displays.hpp"
#include "../L9_Utilities/Log/Log.hpp"

I2cTask::I2cTask(Context& context) 
:   Task(), _context(context), 
    _ioPins(context.GetDomainModels().GetIoPins()),
    _displays(context.GetDomainModels().GetDisplays()),
    _i2cOutputQueue(_context.GetQueues().GetI2cOutputQueue()),
    _i2cOutputQueueReader(_i2cOutputQueue, _ioPins, _displays),
    _i2cTaskDeviceDriversDelegate(context)
{
}

I2cTask::~I2cTask() 
{
}

void I2cTask::Initialize()
{
    _i2cTaskDeviceDriversDelegate.Initialize();
}

void I2cTask::Run()
{
    Log::Entry("I2cTask::Run()");
    while (true)
    {
        while (_i2cOutputQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _i2cTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    Log::Exit("I2cTask::Run()");
}

/* static */ void I2cTask::TaskEntry(void* param)
{
    auto* self = static_cast<I2cTask*>(param);
    self->Run();
}
