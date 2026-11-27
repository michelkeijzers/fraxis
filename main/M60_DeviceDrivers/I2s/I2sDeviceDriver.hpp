#pragma once

#include "II2sDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/DeviceDriver.hpp"
#include <cstdint>
// Do not remove cstddef, needed for size_t in ESP build.
#include <cstddef>

namespace M80::I2s
{
    class II2sService;
}

namespace M81::RtosTask
{
    class IRtosTask;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M60::I2s
{
    class I2sDeviceDriver : public DeviceDriver, public II2sDeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        I2sDeviceDriver(
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        I2sDeviceDriver(
            const I2sDeviceDriver&) = delete;
        
        I2sDeviceDriver& operator=(
            const I2sDeviceDriver&) = delete;
        
        I2sDeviceDriver(I2sDeviceDriver&&) = delete;
        
        I2sDeviceDriver& operator=(
            I2sDeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~I2sDeviceDriver() override;

        M80::I2s::II2sService& GetI2s() override;
        
        void SetI2s(
            M80::I2s::II2sService& i2s) override;

        void SetConfiguration(
            uint8_t port,
            uint8_t bclkPin,
            uint8_t wsPin,
            uint8_t dinPin,
            uint8_t doutPin,
            uint32_t sampleRate,
            uint16_t bitsPerSample,
            uint8_t channels) override;

        void SetRtosTask(
            M81::RtosTask::IRtosTask& rtosTask);

        void Initialize() override;

        size_t Read(
            void* buffer,
            size_t length,
            uint32_t timeoutInMs) override;

        size_t Write(
            const void* buffer,
            size_t length,
            uint32_t timeoutInMs) override;

        bool Start() override;

        bool Stop() override;

    private:
        uint8_t _port;
        
        uint8_t _bclkPin;
        
        uint8_t _wsPin;
        
        uint8_t _dinPin;
        
        uint8_t _doutPin;
        
        uint32_t _sampleRate;
        
        uint16_t _bitsPerSample;
        
        uint8_t _channels;

        M80::I2s::II2sService* _i2s;
        
        M81::RtosTask::IRtosTask* _rtosTask;
    };
}