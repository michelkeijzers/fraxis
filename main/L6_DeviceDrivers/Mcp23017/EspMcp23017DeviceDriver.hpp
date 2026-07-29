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
    Mcp23017DeviceModel& GetMcp23017DeviceModel();
    
private:
    void SendInputPinsMask() override;
    void InitializeInterrupts() override;
    void InitializeInterruptOnEsp();
    void InitializeInterruptOnMcp23017(); 
    bool HasInterruptTriggered() const override;
    uint16_t ReadLastInterrupGpioStates() override;
};
