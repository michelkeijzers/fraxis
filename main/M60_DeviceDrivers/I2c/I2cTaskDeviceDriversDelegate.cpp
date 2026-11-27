#include "I2cTaskDeviceDriversDelegate.hpp"
#include "../../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../M50_DeviceModels/I2c/Mcp23017/IMcp23017DeviceModel.hpp"
#include "../../M60_DeviceDrivers/I2c/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2c/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include "../../M90_Utilities/Time/ITimeUtilities.hpp"

namespace M60::I2c
{
    I2cTaskDeviceDriversDelegate::I2cTaskDeviceDriversDelegate(
        I2cInputQueueWriter& inputQueueWriter,
        IoPins& ioPins,
        M50::I2c::IMcp23017DeviceModel& mcp23017DeviceModel,
        M60::I2c::ILcd2004DeviceDriver& lcd2004DeviceDriver,
        M60::I2c::IMcp23017DeviceDriver& mcp23017DeviceDriver,
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::Time::ITimeUtilities& timeUtilities)
    : 
        TaskDeviceDriversDelegate(assert, log),
        _i2cInputQueueWriter(inputQueueWriter),
        _ioPins(ioPins),
        _mcp23017DeviceModel(mcp23017DeviceModel),
        _lcd2004DeviceDriver(lcd2004DeviceDriver),
        _mcp23017DeviceDriver(mcp23017DeviceDriver),
        _assert(assert),
        _timeUtilities(timeUtilities),
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
            _mcp23017DeviceModel.SetGpioStates(gpioStates);
            _ioPins.UpdateInputs();
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
