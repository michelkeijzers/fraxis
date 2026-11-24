#include "I2cTaskDeviceDriversDelegate.hpp"
#include "../../M10_Composition/Context/DeviceModelsContext.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../M50_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../M60_DeviceDrivers/I2c/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2c/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include "../../M90_Utilities/Time/ITimeUtilities.hpp"

namespace M60::I2c
{
    I2cTaskDeviceDriversDelegate::I2cTaskDeviceDriversDelegate(
        Context& context,
        M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver,
        M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        M90::Time::ITimeUtilities& timeUtilities)
    : 
        _lcd2004DeviceDriver(lcd2004DeviceDriver),
        _mcp23017DeviceDriver(mcp23017DeviceDriver),
        _context(context),
        _assert(assert),
        _timeUtilities(timeUtilities),
        _i2cInputQueueWriter(
            assert, 
            log,
            stringUtilities,
            context.GetQueues().GetI2cInputQueue(), 
            context.GetDomainModels().GetIoPins()),
        _lastMcpWriteUs(0),
        _lastLcdWriteUs(0)
    {
        // No functionality required.
    }

    void I2cTaskDeviceDriversDelegate::Initialize() // NOSONAR: no const to be consequent
    {
        // No actions required.
    }


    void I2cTaskDeviceDriversDelegate::Run()
    {
        std::chrono::microseconds nowUs = _timeUtilities.GetCurrentTimeInUs();
        if (std::chrono::microseconds lcdIntervalUs =
            _timeUtilities.FrequencyToIntervalUs(LCD2004_WRITE_DISPLAY_FREQUENCY);
            nowUs - _lastLcdWriteUs >= lcdIntervalUs)
        {
            _lcd2004DeviceDriver.Update();
            _lastLcdWriteUs = nowUs;
        }

        if (_mcp23017DeviceDriver.HasInterruptTriggered())
        {
            uint16_t gpioStates = _mcp23017DeviceDriver.ReadLastInterrupGpioStates();
            _context.GetDeviceModels().GetMcp23017DeviceModel().SetGpioStates(gpioStates);
            _context.GetDomainModels().GetIoPins().UpdateInputs();
            _i2cInputQueueWriter.SendMessages();
        }

        if (std::chrono::microseconds mcpIntervalUs =
            _timeUtilities.FrequencyToIntervalUs(MCP23017_WRITE_GPIOS_FREQUENCY);
            nowUs - _lastMcpWriteUs >= mcpIntervalUs)
        {
            _mcp23017DeviceDriver.WriteToDriver();
            _lastMcpWriteUs = nowUs;
        }
    }
}
