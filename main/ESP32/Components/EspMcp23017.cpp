#include "EspMcp23017.hpp"
#include "../EspI2c.hpp"
#include "EspMcp23017Registers.hpp"

static constexpr uint8_t I2C_ADDR      = 0x27;

EspMcp23017::EspMcp23017(EspI2c& i2c) : _espI2c(i2c), _ioDirectionPortA(0), _ioDirectionPortB(0)
{
}

EspMcp23017::~EspMcp23017()
{
}

void EspMcp23017::Initialize()
{
}

void EspMcp23017::SetDirectionBytes(uint8_t ioDirectionPortA, uint8_t ioDirectionPortB)
{
    _ioDirectionPortA = ioDirectionPortA;
    _ioDirectionPortB = ioDirectionPortB;

    _espI2c.WriteRegister(I2C_ADDR, MCP_IODIRA, &ioDirectionPortA, 1);
    _espI2c.WriteRegister(I2C_ADDR, MCP_IODIRB, &ioDirectionPortB, 1);
}

uint16_t EspMcp23017::UpdateInputsAndOutputs(uint16_t states)
{
    // Extract output bits from caller
    uint8_t outA = (uint8_t)(states & 0xFF);
    uint8_t outB = (uint8_t)((states >> 8) & 0xFF);

    // Mask out input bits (IODIR = 1 = input). This ensures we NEVER write input pins.
    outA &= ~_ioDirectionPortA;
    outB &= ~_ioDirectionPortB;

    // Write outputs
    _espI2c.WriteRegister(I2C_ADDR, MCP_GPIOA, &outA, 1);
    _espI2c.WriteRegister(I2C_ADDR, MCP_GPIOB, &outB, 1);

    // 4. Read back GPIOA/GPIOB, MCP23017 returns input bits for input pins, output latch bits for output pins
    uint8_t inA = 0;
    uint8_t inB = 0;

    _espI2c.ReadRegister(I2C_ADDR, MCP_GPIOA, &inA, 1);
    _espI2c.ReadRegister(I2C_ADDR, MCP_GPIOB, &inB, 1);

    // Combine into 16-bit result
    return (uint16_t)((inB << 8) | inA);
}
