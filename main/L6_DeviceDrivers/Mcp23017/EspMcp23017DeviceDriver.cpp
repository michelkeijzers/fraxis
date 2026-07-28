#include "EspMcp23017DeviceDriver.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../I2c/I2cDeviceDriver.hpp"
#include "EspMcp23017Registers.hpp"
#include "driver/i2c.h"

EspMcp23017DeviceDriver::EspMcp23017DeviceDriver()
{
}

EspMcp23017DeviceDriver::~EspMcp23017DeviceDriver()
{
}

void EspMcp23017DeviceDriver::Initialize()
{
    SendInputPinsMask();
}

void EspMcp23017DeviceDriver::SendInputPinsMask()
{
    auto* mcp23017DeviceModel = static_cast<Mcp23017DeviceModel*>(&GetDeviceModel());
    uint16_t inputPinsMask = mcp23017DeviceModel->GetInputPinsMask();

    uint8_t directionPortA = inputPinsMask >> 8;
    uint8_t directionPortB = inputPinsMask & 0xFF;

    auto& deviceDriver = GetI2cDeviceDriver();
    deviceDriver.WriteRegister(mcp23017DeviceModel->GetI2cAddress(), MCP_IODIRA, &directionPortA, 1);
    GetI2cDeviceDriver().WriteRegister(mcp23017DeviceModel->GetI2cAddress(), MCP_IODIRB, &directionPortB, 1);
}

uint16_t EspMcp23017DeviceDriver::ReadGpio()
{
    uint8_t portA = 0;
    uint8_t portB = 0;

    auto& deviceDriver = GetI2cDeviceDriver();
    uint8_t i2cChannel = GetI2cAddress();
    deviceDriver.ReadRegister(i2cChannel, MCP_GPIOA, &portA, 1);
    deviceDriver.ReadRegister(i2cChannel, MCP_GPIOB, &portB, 1);
    return (static_cast<uint16_t>(portA) << 8) | portB;
}

void EspMcp23017DeviceDriver::WriteGpio(uint16_t gpioStates)
{
    uint8_t portA = (gpioStates >> 8) & 0xFF;
    uint8_t portB = gpioStates & 0xFF;

    auto& deviceDriver = GetI2cDeviceDriver();
    uint8_t i2cChannel = GetI2cAddress();

    deviceDriver.WriteRegister(i2cChannel, MCP_OLATA, &portA, 1);
    deviceDriver.WriteRegister(i2cChannel, MCP_OLATB, &portB, 1);
}
