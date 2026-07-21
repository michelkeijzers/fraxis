#pragma once

#include "Mcp23017Driver.hpp"
#include "../../../Core/Components/PinIoMappings.hpp"
#include <cstdint>

class WindowsMcp23017Driver : public Mcp23017Driver
{
public:
    WindowsMcp23017Driver(Mcp23017Model& model, I2c& i2c);

    void Initialize() override;
    
    uint16_t ReadGpio() override;
    /// TODO void WriteGpio(uint16_t gpioStates) override;

    // Windows only.
    void SimulateSetGpioPin(PinIoMappings::EIdBit idBit, uint8_t value);
    void SimulateResetGpioPins();
};
