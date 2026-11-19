#include "I2cTask.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M90_Utilities/Log/Log.hpp"
#include "../M90_Utilities/Assert/Assert.hpp"

I2cTask::I2cTask(
    Context& context,
    M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver,
    M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver,
    M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
    M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
    M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities)
:
    _context(context), 
    _assert(assert),
    _lcd2004(context.GetDomainModels().GetLcd2004()),
    _tm1637CentralPanel(context.GetDomainModels().GetTm1637CentralPanel()),
    _tm1637Player1(context.GetDomainModels().GetTm1637Player1()),
    _tm1637Player2(context.GetDomainModels().GetTm1637Player2()),
    _ioPins(context.GetDomainModels().GetIoPins()),
    _i2cOutputQueue(_context.GetQueues().GetI2cOutputQueue()),

    _i2cOutputQueueReader(
        assert, 
        stringUtilities,
        _i2cOutputQueue, 
        _lcd2004, 
        _tm1637CentralPanel, 
        _tm1637Player1, 
        _tm1637Player2, 
        _ioPins),
    
    _i2cTaskDeviceDriversDelegate(
        context, 
        lcd2004DeviceDriver,
        mcp23017DeviceDriver, 
        tm1637DeviceDriverCentralPanel,
        tm1637DeviceDriverPlayer1,
        tm1637DeviceDriverPlayer2,
        assert,
        stringUtilities)
{
}

void I2cTask::Initialize()
{
    _i2cTaskDeviceDriversDelegate.Initialize();
}

void I2cTask::Run()
{
    M90::Log::Log::Entry(Types::ETaskId::I2cTask, "I2cTask::Run()");
    while (true)
    {
        while (_i2cOutputQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _i2cTaskDeviceDriversDelegate.Run();
        GetRtosTask().DelayTask(1);
    }
    M90::Log::Log::Exit(Types::ETaskId::I2cTask, "I2cTask::Run()");
}

/* static */ void I2cTask::TaskEntry(
    void* param) // NOSONAR: RTOS task entry must use void* by design
{
    auto* self = static_cast<I2cTask*>(param);
    self->Run();
}
