#pragma once

#include "Mcp23017DeviceDriver.hpp"

class EspMcp23017DeviceDriver : public Mcp23017DeviceDriver
{
public:
    EspMcp23017DeviceDriver();
    ~EspMcp23017DeviceDriver();

    void Initialize() override;

    uint16_t ReadGpio();
    void WriteGpio(uint16_t gpioStates);
    
private:
    void SendInputPinsMask();
};
