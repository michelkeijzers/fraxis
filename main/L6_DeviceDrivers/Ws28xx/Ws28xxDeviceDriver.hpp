#pragma once

#include "../DeviceDriver.hpp"

class Ws28xxDeviceDriver : public DeviceDriver
{
public:
    Ws28xxDeviceDriver();
    ~Ws28xxDeviceDriver();

    void Initialize() override;
};
