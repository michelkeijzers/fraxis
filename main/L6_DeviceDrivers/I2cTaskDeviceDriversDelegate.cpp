#include "I2cTaskDeviceDriversDelegate.hpp"
#include "../L1_Composition/Context/DeviceModelsContext.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../L9_Utilities/Time/TimeUtilities.hpp"

I2cTaskDeviceDriversDelegate::I2cTaskDeviceDriversDelegate(Context& context) 
: _context(context)
{
}

I2cTaskDeviceDriversDelegate::~I2cTaskDeviceDriversDelegate() 
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

    uint64_t mcpIntervalUs = TimeUtilities::FrequencyToIntervalUs(MCP23017_WRITE_GPIOS_FREQUENCY);
    if (nowUs - _lastMcpWriteUs >= mcpIntervalUs)
    {
        _context.GetDeviceDrivers().GetMcp23017DeviceDriver().WriteToDriver();
        _lastMcpWriteUs = nowUs;
    }
}
