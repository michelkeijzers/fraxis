#ifdef ESP_PLATFORM

#include "EspMcp23017DeviceDriver.hpp"
#include "EspMcp23017Registers.hpp"
#include "../I2c/I2cDeviceDriver.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

EspMcp23017DeviceDriver::EspMcp23017DeviceDriver()
{
}

EspMcp23017DeviceDriver::~EspMcp23017DeviceDriver()
{
}

void EspMcp23017DeviceDriver::SendInputPinsMask()
{
}

void EspMcp23017DeviceDriver::InitializeInterrupts()
{
    /// @todo
}

uint16_t EspMcp23017DeviceDriver::ReadLastInterrupGpioStates()
{
    /// @todo
}

void EspMcp23017DeviceDriver::WriteGpio(uint16_t gpioStates)
{
    /// @todo
}

bool EspMcp23017DeviceDriver::HasInterruptTriggered() const
{
    /// @todo
    return false; 
}

#endif // ESP_PLATFORM
