#pragma once

#include "II2cDeviceDriver.hpp"
#include "../DeviceDriver.hpp"
#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::String
{
    class IStringUtilities;
}

namespace M60::I2c
{
    class I2cDeviceDriver : public DeviceDriver, public II2cDeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        I2cDeviceDriver(
            uint8_t port,
            uint8_t sdaPin,
            uint8_t sclPin,
            uint32_t frequency,
            M80::I2c::II2c& i2c,
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        I2cDeviceDriver(
            const I2cDeviceDriver&) = delete;
        
        I2cDeviceDriver& operator=(
            const I2cDeviceDriver&) = delete;
        
        I2cDeviceDriver(
            I2cDeviceDriver&&) = delete;
        
        I2cDeviceDriver& operator=(
            I2cDeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~I2cDeviceDriver() override = default;

        M80::I2c::II2c& GetI2c() override;
                
        void Initialize() override;

        void Read(
            uint8_t deviceAddress,
            uint8_t* data,
            size_t length) override;

        void Write(
            uint8_t deviceAddress,
            const uint8_t* data,
            size_t length) override;

        uint8_t ReadRegister(
            uint8_t deviceAddress,
            uint8_t registerAddress) override;

        void ReadRegister(
            uint8_t deviceAddress,
            uint8_t registerAddress,
            uint8_t* data,
            size_t length) override;

        void WriteRegister(
            uint8_t deviceAddress,
            uint8_t registerAddress,
            uint8_t data) override;

        void WriteRegister(
            uint8_t deviceAddress,
            uint8_t registerAddress,
            const uint8_t* data,
            size_t length) override;

    private:
        void AssertValidPort(
            uint8_t port);

        uint8_t _port;
       
        uint8_t _sdaPin;
        
        uint8_t _sclPin;
        
        uint32_t _frequency;

        M80::I2c::II2c& _i2c;
    };
}
