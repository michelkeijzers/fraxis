#include "SpiTaskDeviceDriversDelegate.hpp"
#include "MicroSdCard/MIcroSdCardDeviceDriver.hpp"
#include "../M10_Composition/Context/DeviceModelsContext.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../M90_Utilities/Time/TimeUtilities.hpp"
#include "../M90_Utilities/Assert/Assert.hpp"
#include <array>

SpiTaskDeviceDriversDelegate::SpiTaskDeviceDriversDelegate(Context& context) 
:   
    _context(context), 
    _spiInputQueueWriter(context.GetQueues().GetSpiInputQueue(), context.GetDomainModels().GetMicroSdCard())
{
}

void SpiTaskDeviceDriversDelegate::Initialize() // NOSONAR: no const to be consequent
{
    // No actions required.
}


void SpiTaskDeviceDriversDelegate::Run()
{
    //TODOSPI
    //uint64_t nowUs = TimeUtilities::GetCurrentTimeInUs();
    // if (uint64_t lcdIntervalUs = TimeUtilities::FrequencyToIntervalUs(LCD2004_WRITE_DISPLAY_FREQUENCY); 
    //     nowUs - _lastLcdWriteUs >= lcdIntervalUs)
    // {
    //     _context.GetDeviceDrivers().GetLcd2004DeviceDriver().Update();
    //     _lastLcdWriteUs = nowUs;
    // }

    // auto& mcp23017DeviceDriver = _context.GetDeviceDrivers().GetMcp23017DeviceDriver();
    // if (mcp23017DeviceDriver.HasInterruptTriggered())
    // {
    //     uint16_t gpioStates = mcp23017DeviceDriver.ReadLastInterrupGpioStates();
    //     _context.GetDeviceModels().GetMcp23017DeviceModel().SetGpioStates(gpioStates);
    //     _context.GetDomainModels().GetIoPins().UpdateInputs();
    //     _i2cInputQueueWriter.SendMessages();
    // } 

    // if (uint64_t mcpIntervalUs = TimeUtilities::FrequencyToIntervalUs(MCP23017_WRITE_GPIOS_FREQUENCY); 
    //     nowUs - _lastMcpWriteUs >= mcpIntervalUs)
    // {
    //     mcp23017DeviceDriver.WriteToDriver();
    //     _lastMcpWriteUs = nowUs;
    // }

    // uint64_t tm1637IntervalUs = TimeUtilities::FrequencyToIntervalUs(TM1637_WRITE_DISPLAY_FREQUENCY);
    // if (nowUs - _lastTm1637WriteUs >= tm1637IntervalUs)
    // {

    //     auto& deviceDriver = _context.GetDeviceDrivers().GetTm1637DeviceDriverId(_nextTm1637IdToUpdate);
    //     deviceDriver.SendToDisplay();
    //     _nextTm1637IdToUpdate = static_cast<Types::ETm1637Id>((static_cast<uint8_t>(_nextTm1637IdToUpdate) + 1) % 3);
    //     _lastTm1637WriteUs = nowUs;
    // }
}
