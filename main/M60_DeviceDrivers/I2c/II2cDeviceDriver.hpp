#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>
// Do not remove cstddef, needed for size_t in ESP build.
#include <cstddef>

namespace M80::I2c
{
    class II2c;
}

namespace M60::I2c
{
    class II2cDeviceDriver
    {
    public:
        II2cDeviceDriver() = default;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        virtual ~II2cDeviceDriver() = default;

        virtual M80::I2c::II2c& GetI2c() = 0;

        virtual void Initialize() = 0;

        virtual void Read(
            uint8_t deviceAddress,
            uint8_t* data,
            size_t length) = 0;

        virtual void Write(
            uint8_t deviceAddress,
            const uint8_t* data,
            size_t length) = 0;

        virtual uint8_t ReadRegister(
            uint8_t deviceAddress,
            uint8_t registerAddress) = 0;

        virtual void ReadRegister(
            uint8_t deviceAddress,
            uint8_t registerAddress,
            uint8_t* data,
            size_t length) = 0;

        virtual void WriteRegister(
            uint8_t deviceAddress,
            uint8_t registerAddress,
            uint8_t data) = 0;

        virtual void WriteRegister(
            uint8_t deviceAddress,
            uint8_t registerAddress,
            const uint8_t* data,
            size_t length) = 0;
    };
}
