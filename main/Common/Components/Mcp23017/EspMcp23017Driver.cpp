#include "EspMcp23017Driver.hpp"
#include "../I2c/EspI2c.hpp"
#include "EspMcp23017Registers.hpp"
#include "Mcp23017Model.hpp"

static const uint8_t I2C_ADDR = 27;

EspMcp23017Driver::EspMcp23017Driver(Mcp23017Model& model, I2c& i2c) 
: Mcp23017Driver(model, i2c)
{
}

void EspMcp23017Driver::Initialize()
{
    SendInputPinsMask();
}

void EspMcp23017Driver::SendInputPinsMask()
{
    uint16_t inputPinsMask = _model.GetInputPinsMask();
    uint8_t directionPortA = inputPinsMask >> 8;
    uint8_t directionPortB = inputPinsMask & 0xFF;

    _i2c.WriteRegister(I2C_ADDR, MCP_IODIRA, &directionPortA, 1);
    _i2c.WriteRegister(I2C_ADDR, MCP_IODIRB, &directionPortB, 1);
}

uint16_t EspMcp23017Driver::ReadGpio()
{
    uint8_t portA = 0;
    uint8_t portB = 0;

    _i2c.ReadRegister(I2C_ADDR, MCP_GPIOA, &portA, 1);
    _i2c.ReadRegister(I2C_ADDR, MCP_GPIOB, &portB, 1);
    return (static_cast<uint16_t>(portA) << 8) | portB;
}

/// TODO 
// void Mcp23017Driver::WriteGpio(uint16_t gpioStates)
// {
//     uint8_t portA = (gpioStates >> 8) & 0xFF;
//     uint8_t portB = gpioStates & 0xFF;

//     _i2c.WriteRegister(I2C_ADDR, MCP_GPIOA, &portA, 1);
//     _i2c.WriteRegister(I2C_ADDR, MCP_GPIOB, &portB, 1);
// }
