#pragma once

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
    class II2sDeviceDriver
    {
    public:
        virtual ~II2sDeviceDriver() = default;

        virtual M80::I2s::II2sService& GetI2s() = 0;
        
        virtual void SetI2s(
            M80::I2s::II2sService& i2s) = 0;

        virtual void SetConfiguration(
            uint8_t port,
            uint8_t bclkPin,
            uint8_t wsPin,
            uint8_t dinPin,
            uint8_t doutPin,
            uint32_t sampleRate,
            uint16_t bitsPerSample,
            uint8_t channels) = 0;

        virtual void SetRtosTask(
            M81::RtosTask::IRtosTask& rtosTask) = 0;

        virtual size_t Read(
            void* buffer,
            size_t length,
            uint32_t timeoutInMs) = 0;

        virtual size_t Write(
            const void* buffer,
            size_t length,
            uint32_t timeoutInMs) = 0;

        virtual bool Start() = 0;

        virtual bool Stop() = 0;
    };
}