#pragma once

#include "../I2c/EspI2c.hpp"
#include "Mcp23017Driver.hpp"

class Mcp23017Model;
class EspI2c;

class EspMcp23017Driver : public Mcp23017Driver
{
public:
    EspMcp23017Driver(Mcp23017Model& model, I2c& i2c);

    void Initialize() override;
    
    uint16_t ReadGpio() override;
    /// TODO void WriteGpio(uint16_t gpioStates) override;

private:
    void SendInputPinsMask();
};
