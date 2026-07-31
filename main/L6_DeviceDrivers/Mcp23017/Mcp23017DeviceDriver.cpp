#include "Mcp23017DeviceDriver.hpp"
#include "InterruptHandler.hpp"
#include "Mcp23017Registers.hpp"
#include "../I2c/I2cDeviceDriver.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L8_Services/Gpio/Gpio.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

#ifdef ESP_PLATFORM
    #include "esp_attr.h"
#else // Windows
    #define IRAM_ATTR 
#endif // ESP_PLATFORM

volatile static bool g_mcpInterruptTriggered = false;

// static void IRAM_ATTR McpInterruptHandler(void* arg)
// {
//     Mcp23017DeviceDriver::SetInterruptTriggered();
// }

Mcp23017DeviceDriver::Mcp23017DeviceDriver()
: _enableInterrupt(false), _interruptPin(0), _i2cDeviceDriver(nullptr), _i2cAddress(0)
{
}

Mcp23017DeviceDriver::~Mcp23017DeviceDriver()
{
}

void Mcp23017DeviceDriver::SetInterruptConfiguration(bool enableInterrupt, uint8_t interruptPin)
{
    _enableInterrupt = enableInterrupt;
    _interruptPin = interruptPin;
}

I2cDeviceDriver& Mcp23017DeviceDriver::GetI2cDeviceDriver() 
{
    return *_i2cDeviceDriver; 
}

void Mcp23017DeviceDriver::SetI2cDeviceDriver(I2cDeviceDriver& i2cDeviceDriver)
{
    _i2cDeviceDriver = &i2cDeviceDriver; 
}

void Mcp23017DeviceDriver::SendInputPinsMask()
{
    auto& mcp23017DeviceModel = GetMcp23017DeviceModel();
    uint16_t inputPinsMask = mcp23017DeviceModel.GetInputPinsMask();

    uint8_t directionPortA = inputPinsMask >> 8;
    uint8_t directionPortB = inputPinsMask & 0xFF;

    auto& deviceDriver = GetI2cDeviceDriver();
    deviceDriver.WriteRegister(mcp23017DeviceModel.GetI2cAddress(), MCP23017_IODIRA, &directionPortA, 1);
    deviceDriver.WriteRegister(mcp23017DeviceModel.GetI2cAddress(), MCP23017_IODIRB, &directionPortB, 1);
}

void Mcp23017DeviceDriver::Initialize()
{
    SendInputPinsMask();
    if (_enableInterrupt)
    {
        InitializeInterrupts();
    }
}

void Mcp23017DeviceDriver::InitializeInterrupts()
{
    InitializeInterruptOnEsp(_interruptPin);
    InitializeInterruptOnMcp23017();
}

void Mcp23017DeviceDriver::InitializeInterruptOnEsp(uint8_t interruptPin)
{
    GetGpio().ConfigAsInterruptInput(interruptPin);
    GetGpio().InstallIsrService();
    GetGpio().AddInterruptHandler(interruptPin, InterruptHandler, nullptr);
}

void Mcp23017DeviceDriver::InitializeInterruptOnMcp23017()
{
    auto& deviceDriver = GetI2cDeviceDriver();
    auto& mcp23017DeviceModel = GetMcp23017DeviceModel();
    uint16_t inputPinsMask = mcp23017DeviceModel.GetInputPinsMask();

    deviceDriver.WriteRegister(MCP23017_GPINTENA, inputPinsMask >> 8, 1); // Port A
    deviceDriver.WriteRegister(MCP23017_GPINTENB, inputPinsMask & 0xFF, 1); // Port B

    // Compare against previous value (default).
    deviceDriver.WriteRegister(MCP23017_INTCONA, 0x00, 1);
    deviceDriver.WriteRegister(MCP23017_INTCONB, 0x00, 1);

    // Clear interrupt flags.
    deviceDriver.ReadRegister(MCP23017_INTCAPA, 1);
    deviceDriver.ReadRegister(MCP23017_INTCAPB, 1);
}

Gpio& Mcp23017DeviceDriver::GetGpio()
{
    return *_gpio;
}

void Mcp23017DeviceDriver::SetGpio(Gpio& gpio)
{
    _gpio = &gpio;
}

/// @brief Reads GPIO states from last interrupt.
/// @details ReadRegister of INTCAPA/B does NOT reset output pins and leaves the actual output state unchanged.
/// @return 
uint16_t Mcp23017DeviceDriver::ReadLastInterrupGpioStates()
{
    Assert::IsTrue(g_mcpInterruptTriggered, "Interrupt not triggered");
    g_mcpInterruptTriggered = false;

    auto& deviceDriver = GetI2cDeviceDriver();
    uint8_t capA = deviceDriver.ReadRegister(_i2cAddress, MCP23017_INTCAPA);
    uint8_t capB = deviceDriver.ReadRegister(_i2cAddress, MCP23017_INTCAPB);
    return (capA << 8) | capB;
}

Mcp23017DeviceModel& Mcp23017DeviceDriver::GetMcp23017DeviceModel()
{
    return static_cast<Mcp23017DeviceModel&>(GetDeviceModel());
}

bool Mcp23017DeviceDriver::HasInterruptTriggered() const
{
    return g_mcpInterruptTriggered;
}

/// @brief Sets interrupt triggered flag. This is the interrupt handler for the MCP23017 interrupt pin.
/* static */ void Mcp23017DeviceDriver::SetInterruptTriggered()
{
    g_mcpInterruptTriggered = true;
}

void Mcp23017DeviceDriver::WriteToDriver()
{
    auto& mcp23017DeviceModel = GetMcp23017DeviceModel();
    if (mcp23017DeviceModel.IsDirty())
    {
        uint16_t gpioStates = mcp23017DeviceModel.GetGpioStates();
        WriteGpios(gpioStates);
        mcp23017DeviceModel.ClearDirty();
    }
}

void Mcp23017DeviceDriver::WriteGpios(uint16_t gpioStates)
{
    uint8_t portA = (gpioStates >> 8) & 0xFF;
    uint8_t portB = gpioStates & 0xFF;

    auto& deviceDriver = GetI2cDeviceDriver();
    deviceDriver.WriteRegister(_i2cAddress, MCP23017_OLATA, &portA, 1);
    deviceDriver.WriteRegister(_i2cAddress, MCP23017_OLATB, &portB, 1);
}
