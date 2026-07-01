#pragma once

#include "../EspI2c.hpp"
#include "../../Core/Components/Mcp23017.hpp"

class EspMcp23017 : public Mcp23017
{
public:
    EspMcp23017(EspI2c& i2c);
    ~EspMcp23017();

    void Initialize() override;
    void SetDirectionBytes(uint8_t iodira, uint8_t iodirb) override;

    uint16_t GetGpioStates() const override;
    void SetGpioStates(uint16_t gpioStates) override;

private:
	EspI2c& _espI2c;
};
