#ifdef ESP_PLATFORM

#include "EspMcp23017DeviceDriver.hpp"
#include "EspMcp23017Registers.hpp"
#include "../I2c/I2cDeviceDriver.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "driver/i2c.h"
#include "esp_attr.h"

volatile bool g_mcpInterruptFlag = false;

static void IRAM_ATTR InterruptHandler(void* arg)
{
    g_mcpInterruptFlag = true;
}

EspMcp23017DeviceDriver::EspMcp23017DeviceDriver()
{
}

EspMcp23017DeviceDriver::~EspMcp23017DeviceDriver()
{
}

void EspMcp23017DeviceDriver::SendInputPinsMask()
{
    auto& mcp23017DeviceModel = GetMcp23017DeviceModel();
    uint16_t inputPinsMask = mcp23017DeviceModel.GetInputPinsMask();

    uint8_t directionPortA = inputPinsMask >> 8;
    uint8_t directionPortB = inputPinsMask & 0xFF;

    auto& deviceDriver = GetI2cDeviceDriver();
    deviceDriver.WriteRegister(mcp23017DeviceModel.GetI2cAddress(), MCP23017_IODIRA, &directionPortA, 1);
    deviceDriver.WriteRegister(mcp23017DeviceModel.GetI2cAddress(), MCP23017_IODIRB, &directionPortB, 1);
}

void EspMcp23017DeviceDriver::InitializeInterrupts()
{
    InitializeInterruptOnEsp();
    InitializeInterruptOnMcp23017();
}

void EspMcp23017DeviceDriver::InitializeInterruptOnEsp()
{
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE;        // MCP INT is active LOW
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << GetInterruptPin());
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;      // MCP INT is open-drain

    Assert::Equals(gpio_config(&io_conf), ESP_OK, "Failed to configure GPIO");
    Assert::Equals(gpio_install_isr_service(0), ESP_OK, "Failed to install GPIO ISR service");
    Assert::Equals(gpio_isr_handler_add(static_cast<gpio_num_t>(GetInterruptPin()), InterruptHandler, nullptr), ESP_OK, 
        "Failed to add GPIO ISR handler");
}

void EspMcp23017DeviceDriver::InitializeInterruptOnMcp23017()
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

/// @brief Reads GPIO states from last interrupt.
/// @details ReadRegister of INTCAPA/B does NOT reset output pins and leaves the actual output state unchanged.
/// @return 
uint16_t EspMcp23017DeviceDriver::ReadLastInterrupGpioStates()
{
    Assert::IsTrue(HasInterruptTriggered(), "Interrupt not triggered");
    g_mcpInterruptFlag = false;

    auto& deviceDriver = GetI2cDeviceDriver();
    uint8_t i2cChannel = GetI2cAddress();
    uint8_t capA = deviceDriver.ReadRegister(i2cChannel, MCP23017_INTCAPA);
    uint8_t capB = deviceDriver.ReadRegister(i2cChannel, MCP23017_INTCAPB);
    return (capA << 8) | capB;
}

void EspMcp23017DeviceDriver::WriteGpio(uint16_t gpioStates)
{
    uint8_t portA = (gpioStates >> 8) & 0xFF;
    uint8_t portB = gpioStates & 0xFF;

    auto& deviceDriver = GetI2cDeviceDriver();
    uint8_t i2cChannel = GetI2cAddress();
    deviceDriver.WriteRegister(i2cChannel, MCP23017_OLATA, &portA, 1);
    deviceDriver.WriteRegister(i2cChannel, MCP23017_OLATB, &portB, 1);
}
    
bool EspMcp23017DeviceDriver::HasInterruptTriggered() const
{
    return g_mcpInterruptFlag;
}

#endif // ESP_PLATFORM
