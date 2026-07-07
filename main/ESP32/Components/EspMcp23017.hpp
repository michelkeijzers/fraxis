#pragma once

#include "../EspI2c.hpp"
#include "../../Core/Components/Mcp23017.hpp"

class EspMcp23017 : public Mcp23017
{
public:
    EspMcp23017(EspI2c& i2c);
    ~EspMcp23017();

    void Initialize() override;
    void SetDirectionBytes(uint8_t ioDirectionPortA, uint8_t ioDirectionPortB) override;

    uint16_t UpdateInputsAndOutputs(uint16_t gpioStates) override;

private:
	EspI2c& _espI2c;

    uint8_t _ioDirectionPortA;
    uint8_t _ioDirectionPortB;
};
