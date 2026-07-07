#pragma once

#include "../../Core/Components/Mcp23017.hpp"
#include "../../Core/Components/PinIoMappings.hpp"
#include <cstdint>

class WindowsMcp23017 : public Mcp23017
{
public:
    WindowsMcp23017();
    ~WindowsMcp23017();

    void Initialize() override;
    void SetDirectionBytes(uint8_t iodira, uint8_t iodirb) override;

    uint16_t UpdateInputsAndOutputs(uint16_t gpioStates);

    // Windows only.
    void SimulateSetGpioPin(PinIoMappings::EIdBit idBit, uint8_t value);
    void SimulateResetGpioPins();

private:
    uint16_t _gpioStates;
    uint8_t _ioDirectionPortA;
    uint8_t _ioDirectionPortB;
};
