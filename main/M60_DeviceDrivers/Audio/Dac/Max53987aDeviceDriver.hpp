#pragma once

#include "../AudioDeviceDriver.hpp"
#include <cstdint>

class Max53987aDeviceDriver : public AudioDeviceDriver
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Max53987aDeviceDriver();
    
    Max53987aDeviceDriver(const Max53987aDeviceDriver&) = delete;
    Max53987aDeviceDriver& operator=(const Max53987aDeviceDriver&) = delete;
    Max53987aDeviceDriver(Max53987aDeviceDriver&&) = delete;
    Max53987aDeviceDriver& operator=(Max53987aDeviceDriver&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~Max53987aDeviceDriver() override;

    size_t WriteSamples(
        const int16_t* buffer,
        size_t length);
};
