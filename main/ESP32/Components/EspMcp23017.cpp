#include "EspMcp23017.hpp"
#include "../EspI2c.hpp"
#include "EspMcp23017Registers.hpp"

static constexpr uint8_t I2C_ADDR      = 0x27;

EspMcp23017::EspMcp23017(EspI2c& i2c) : _espI2c(i2c)
{
}

EspMcp23017::~EspMcp23017()
{
}

void EspMcp23017::Initialize()
{
}

void EspMcp23017::SetDirectionBytes(uint8_t iodira, uint8_t iodirb)
{
    _espI2c.WriteRegister(I2C_ADDR, MCP_IODIRA, &iodira, 1);
    _espI2c.WriteRegister(I2C_ADDR, MCP_IODIRB, &iodirb, 1);
}

uint16_t EspMcp23017::GetGpioStates() const
{
    uint8_t a = 0;
    uint8_t b = 0;

    // Read GPIOA
    _espI2c.ReadRegister(I2C_ADDR, MCP_GPIOA, &a, 1);

    // Read GPIOB
    _espI2c.ReadRegister(I2C_ADDR, MCP_GPIOB, &b, 1);

    // Combine into 16-bit value
    return (uint16_t)((b << 8) | a);
}


void EspMcp23017::SetGpioStates(uint16_t states)
{
    uint8_t a = (uint8_t)(states & 0xFF);
    uint8_t b = (uint8_t)((states >> 8) & 0xFF);

    // Write GPIOA
    _espI2c.WriteRegister(I2C_ADDR, MCP_GPIOA, &a, 1);

    // Write GPIOB
    _espI2c.WriteRegister(I2C_ADDR, MCP_GPIOB, &b, 1);    
}