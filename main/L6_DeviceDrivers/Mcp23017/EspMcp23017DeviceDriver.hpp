#pragma once

#include "Mcp23017DeviceDriver.hpp"

class EspMcp23017DeviceDriver : public Mcp23017DeviceDriver
{
public:
    EspMcp23017DeviceDriver();
    ~EspMcp23017DeviceDriver();

    void Initialize() override;

protected:
    uint16_t ReadGpio() override;
    void WriteGpio(uint16_t gpioStates) override;
    
private:
    void SendInputPinsMask();
};
