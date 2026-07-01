#include <cstdint>

class Mcp23017
{
public:
    Mcp23017();
    ~Mcp23017();

    virtual void Initialize() = 0;
    virtual void SetDirectionBytes(uint8_t iodira, uint8_t iodirb) = 0;

    virtual uint16_t GetGpioStates() const = 0;
    virtual void SetGpioStates(uint16_t gpioStates) = 0;
};
