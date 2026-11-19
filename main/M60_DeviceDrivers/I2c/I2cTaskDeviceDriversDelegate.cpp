#include "I2cTaskDeviceDriversDelegate.hpp"
#include "Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../../M10_Composition/Context/DeviceModelsContext.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../M40_DomainModels/I2c/Displays/Tm1637/Tm1637.hpp"
#include "../../M50_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../M50_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../M60_DeviceDrivers/I2c/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2c/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2c/Tm1637/Tm1637DeviceDriver.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include <array>

namespace M60::I2c
{
    I2cTaskDeviceDriversDelegate::I2cTaskDeviceDriversDelegate(
        Context& context,
        M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver,
        M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
        M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities)
    : 
        _lcd2004DeviceDriver(lcd2004DeviceDriver),
        _mcp23017DeviceDriver(mcp23017DeviceDriver),
        _tm1637DeviceDriverCentralPanel(tm1637DeviceDriverCentralPanel),
        _tm1637DeviceDriverPlayer1(tm1637DeviceDriverPlayer1),
        _tm1637DeviceDriverPlayer2(tm1637DeviceDriverPlayer2),
        _context(context),
        _assert(assert),
        _i2cInputQueueWriter(
            assert, 
            stringUtilities,
            context.GetQueues().GetI2cInputQueue(), 
            context.GetDomainModels().GetIoPins()),
        _lastMcpWriteUs(0),
        _lastLcdWriteUs(0),
        _lastTm1637WriteUs(0),
        _nextTm1637IdToUpdate(Types::ETm1637Id::CentralPanel)
    {}

    void I2cTaskDeviceDriversDelegate::Initialize() // NOSONAR: no const to be consequent
    {
        // No actions required.
    }


    void I2cTaskDeviceDriversDelegate::Run()
    {
        std::chrono::microseconds nowUs = M90::Time::TimeUtilities::GetCurrentTimeInUs();
        if (std::chrono::microseconds lcdIntervalUs =
            M90::Time::TimeUtilities::FrequencyToIntervalUs(LCD2004_WRITE_DISPLAY_FREQUENCY);
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
            M90::Time::TimeUtilities::FrequencyToIntervalUs(MCP23017_WRITE_GPIOS_FREQUENCY);
            nowUs - _lastMcpWriteUs >= mcpIntervalUs)
        {
            _mcp23017DeviceDriver.WriteToDriver();
            _lastMcpWriteUs = nowUs;
        }

        std::chrono::microseconds tm1637IntervalUs =
            M90::Time::TimeUtilities::FrequencyToIntervalUs(TM1637_WRITE_DISPLAY_FREQUENCY);
        if (nowUs - _lastTm1637WriteUs >= tm1637IntervalUs)
        {

            auto& deviceDriver = GetTm1637DeviceDriverId(_nextTm1637IdToUpdate);
            deviceDriver.SendToDisplay();
            _nextTm1637IdToUpdate =
                static_cast<Types::ETm1637Id>((static_cast<uint8_t>(_nextTm1637IdToUpdate) + 1) % 3);
            _lastTm1637WriteUs = nowUs;
        }
    }

    Tm1637DeviceDriver& I2cTaskDeviceDriversDelegate::GetTm1637DeviceDriverId(
        Types::ETm1637Id tm1637id)
    {
        using enum Types::ETm1637Id;
        switch (tm1637id)
        {
        case CentralPanel: return _tm1637DeviceDriverCentralPanel;
        case Player1:      return _tm1637DeviceDriverPlayer1;
        case Player2:      return _tm1637DeviceDriverPlayer2;
        default:
            _assert.Fail(Types::ETaskId::System, "Illegal TM1637 ID");
        }

        return _tm1637DeviceDriverCentralPanel; // To avoid compiler warning   
    }
}
