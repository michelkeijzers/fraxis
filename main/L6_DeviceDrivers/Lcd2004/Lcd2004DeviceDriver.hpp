#pragma once

#include "../DeviceDriver.hpp"

class Lcd2004DeviceDriver : public DeviceDriver
{
public:
    Lcd2004DeviceDriver();
    ~Lcd2004DeviceDriver();

    void Initialize() override;
};
