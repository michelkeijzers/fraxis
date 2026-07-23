#pragma once

#include "I2cDriver.hpp"

class EspI2cDriver : public I2cDriver
{
public:
    EspI2cDriver();
    ~EspI2cDriver() = default;
};
