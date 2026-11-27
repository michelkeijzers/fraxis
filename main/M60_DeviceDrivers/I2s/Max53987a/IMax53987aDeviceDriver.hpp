#pragma once

// Do not remove cstddef, needed for size_t in ESP build.
#include <cstddef>
#include <cstdint>

namespace M50::I2s
{
    class IMax53987aDeviceModel;
}

namespace M60::I2s
{
    class IMax53987aDeviceDriver
    {
    public:
        virtual ~IMax53987aDeviceDriver() = default;

        virtual void SetMax53987aDeviceModel(
            M50::I2s::IMax53987aDeviceModel& max53987aDeviceModel) = 0;

        virtual M50::I2s::IMax53987aDeviceModel& GetMax53987aDeviceModel() = 0;

        size_t WriteSamples(
            const int16_t* buffer,
            size_t length);
    };
}