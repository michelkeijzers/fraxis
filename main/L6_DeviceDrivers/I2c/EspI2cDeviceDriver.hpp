#pragma once

#include "I2cDeviceDriver.hpp"

class EspI2cDeviceDriver : public I2cDeviceDriver
{
public:
    EspI2cDeviceDriver();
    ~EspI2cDeviceDriver() = default;
};
