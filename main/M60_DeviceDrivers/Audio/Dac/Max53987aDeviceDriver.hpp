#pragma once

#include "../AudioDeviceDriver.hpp"
#include <cstdint>

class Max53987aDeviceDriver : public AudioDeviceDriver
{
public:
    Max53987aDeviceDriver();
    ~Max53987aDeviceDriver() = default;

    size_t WriteSamples(
        const int16_t* buffer,
        size_t length);
};
