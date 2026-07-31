#pragma once

#include "Mcp23017DeviceDriver.hpp"

class Mcp23017DeviceModel;

class EspMcp23017DeviceDriver : public Mcp23017DeviceDriver
{
public:
    EspMcp23017DeviceDriver();
    ~EspMcp23017DeviceDriver();

private:
    void InitializeInterruptOnEsp(uint8_t interruptPin) override;
};
