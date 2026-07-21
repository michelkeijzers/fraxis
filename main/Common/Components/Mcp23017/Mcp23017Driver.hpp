#pragma once

#include <cstdint>

class Mcp23017Model;
class I2c;

class Mcp23017Driver
{
public:
    Mcp23017Driver(Mcp23017Model& model, I2c& i2c);

    virtual void Initialize() = 0;

    /// @brief Reads GPIOs.
    /// @return port A (MSB byte), port B (LSB byte) 
    virtual uint16_t ReadGpio() = 0;

    /// @brief Writes GPIOs.
    /// @param gpioStates port A (MSB byte), port B (LSB byte)
    virtual void WriteGpio(uint16_t gpioStates) = 0;

protected:
    Mcp23017Model& _model;
    I2c& _i2c;
};
