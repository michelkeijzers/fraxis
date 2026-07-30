#include "I2cTaskDeviceDriversDelegate.hpp"
#include "Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L4_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../L9_Utilities/Time/TimeUtilities.hpp"

I2cTaskDeviceDriversDelegate::I2cTaskDeviceDriversDelegate(Context& context) 
:   _context(context), 
    _i2cInputQueueWriter(context.GetQueues().GetI2cInputQueue(), context.GetDomainModels().GetIoPins()),
    _lastMcpWriteUs(0), _lastLcdWriteUs(0), _lastTm1637WriteUs(0), _nextTm1637IdToUpdate(Types::ETm1637Id::CentralPanel)
{
}

I2cTaskDeviceDriversDelegate::~I2cTaskDeviceDriversDelegate() 
{
}

void I2cTaskDeviceDriversDelegate::Initialize() 
{
}

void I2cTaskDeviceDriversDelegate::Run()
{
    uint64_t nowUs = TimeUtilities::GetCurrentTimeInUs();
    uint64_t lcdIntervalUs = TimeUtilities::FrequencyToIntervalUs(LCD2004_WRITE_DISPLAY_FREQUENCY);
    if (nowUs - _lastLcdWriteUs >= lcdIntervalUs)
    {
        _context.GetDeviceDrivers().GetLcd2004DeviceDriver().SendToDisplay();
        _lastLcdWriteUs = nowUs;
    }

    auto& mcp23017DeviceDriver = _context.GetDeviceDrivers().GetMcp23017DeviceDriver();
    if (mcp23017DeviceDriver.HasInterruptTriggered())
    {
        uint16_t gpioStates = mcp23017DeviceDriver.ReadLastInterrupGpioStates();
        _context.GetDeviceModels().GetMcp23017DeviceModel().SetGpioStates(gpioStates);
        _context.GetDomainModels().GetIoPins().UpdateInputs();
        _i2cInputQueueWriter.SendMessages();
    } 

    uint64_t mcpIntervalUs = TimeUtilities::FrequencyToIntervalUs(MCP23017_WRITE_GPIOS_FREQUENCY);
    if (nowUs - _lastMcpWriteUs >= mcpIntervalUs)
    {
        mcp23017DeviceDriver.WriteToDriver();
        _lastMcpWriteUs = nowUs;
    }

    uint64_t tm1637IntervalUs = TimeUtilities::FrequencyToIntervalUs(TM1637_WRITE_DISPLAY_FREQUENCY);
    if (nowUs - _lastTm1637WriteUs >= tm1637IntervalUs)
    {

        auto& deviceDriver = _context.GetDeviceDrivers().GetTm1637DeviceDriverId(_nextTm1637IdToUpdate);
        deviceDriver.SendToDisplay();
        _nextTm1637IdToUpdate = static_cast<Types::ETm1637Id>((static_cast<uint8_t>(_nextTm1637IdToUpdate) + 1) % 3);
        _lastTm1637WriteUs = nowUs;
    }
}
