#pragma once

#include "../DeviceDriver.hpp"

class Tm1637DeviceDriver : public DeviceDriver
{
public:
    Tm1637DeviceDriver();
    ~Tm1637DeviceDriver();

    void Initialize() override;
};
