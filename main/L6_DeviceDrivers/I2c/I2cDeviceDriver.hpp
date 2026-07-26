#pragma once

#include "../DeviceDriver.hpp"

class I2cDeviceDriver : public DeviceDriver
{
public:
    I2cDeviceDriver();
    ~I2cDeviceDriver();

    void Initialize() override;
};
