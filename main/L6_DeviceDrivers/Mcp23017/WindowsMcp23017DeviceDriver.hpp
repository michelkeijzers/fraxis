#pragma once

#include "Mcp23017DeviceDriver.hpp"

class Mcp23017DeviceModel;

class EspMcp23017DeviceDriver : public Mcp23017DeviceDriver
{
public:
    EspMcp23017DeviceDriver();
    ~EspMcp23017DeviceDriver();

protected:
    void WriteGpio(uint16_t gpioStates) override;
    
    void SendInputPinsMask() override;
    void InitializeInterrupts() override;
    bool HasInterruptTriggered() const override;
    uint16_t ReadLastInterrupGpioStates() override;
};
