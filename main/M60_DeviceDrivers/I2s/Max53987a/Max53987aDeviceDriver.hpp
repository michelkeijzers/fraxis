#pragma once

#include "../I2sDeviceDriver.hpp"
#include <cstdint>

namespace M60::I2s
{
    class Max53987aDeviceDriver : public I2sDeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        Max53987aDeviceDriver(
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);
        
        Max53987aDeviceDriver(
            const Max53987aDeviceDriver&) = delete;
        
        Max53987aDeviceDriver& operator=(
            const Max53987aDeviceDriver&) = delete;
        
        Max53987aDeviceDriver(
            Max53987aDeviceDriver&&) = delete;
        
        Max53987aDeviceDriver& operator=(
            Max53987aDeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~Max53987aDeviceDriver() override;

        size_t WriteSamples(
            const int16_t* buffer,
            size_t length);
    };
}