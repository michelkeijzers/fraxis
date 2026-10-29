#pragma once

#include <cstdint>

class DeviceConstants
{
public:
    static constexpr uint32_t I2C_FREQUENCY_STANDARD_MODE   = 100'000;
    static constexpr uint32_t I2C_FREQUENCY_FAST_MODE       = 400'000;
};
