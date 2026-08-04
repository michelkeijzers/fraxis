#include "I2cTask.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L9_Utilities/Log/Log.hpp"

I2cTask::I2cTask(Context& context) 
:   Task(), 
    _context(context), 
    _lcd2004(context.GetDomainModels().GetLcd2004()),
    _tm1637CentralPanel(context.GetDomainModels().GetTm1637CentralPanel()),
    _tm1637Player1(context.GetDomainModels().GetTm1637Player1()),
    _tm1637Player2(context.GetDomainModels().GetTm1637Player2()),
    _ioPins(context.GetDomainModels().GetIoPins()),
    _i2cOutputQueue(_context.GetQueues().GetI2cOutputQueue()),
    _i2cOutputQueueReader(_i2cOutputQueue, _lcd2004, _tm1637CentralPanel, _tm1637Player1, _tm1637Player2, _ioPins),
    _i2cTaskDeviceDriversDelegate(context)
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


/* static */ void I2cTask::TaskEntry(
    void* param) // NOSONAR: RTOS task entry must use void* by design
{
    auto* self = static_cast<I2cTask*>(param);
    self->Run();
}
