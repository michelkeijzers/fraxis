#include "I2cTaskDeviceDriversDelegate.hpp"
#include "Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L4_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../L9_Utilities/Time/TimeUtilities.hpp"

I2cTaskDeviceDriversDelegate::I2cTaskDeviceDriversDelegate(Context& context) 
: _context(context), _i2cInputQueueWriter(context.GetQueues().GetI2cInputQueue(), context.GetDomainModels().GetIoPins())
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
    uint64_t nowUs = 0; // TODO get current time

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
}
