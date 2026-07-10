#include "PinIo.hpp"
#include <cstdint>

class Mcp23017
{
public:
    virtual void Initialize() = 0;
    virtual void SetDirectionBytes(uint8_t iodira, uint8_t iodirb) = 0;

    virtual uint16_t UpdateInputsAndOutputs(uint16_t gpioStates) = 0;
};
