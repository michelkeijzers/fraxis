#pragma once

#include "../DeviceDriver.hpp"

class Mcp23017DeviceDriver : public DeviceDriver
{
public:
    Mcp23017DeviceDriver();
    ~Mcp23017DeviceDriver();

    void Initialize() override;
};
