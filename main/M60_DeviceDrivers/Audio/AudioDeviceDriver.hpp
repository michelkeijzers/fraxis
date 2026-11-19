#pragma once

#include "../../M60_DeviceDrivers/DeviceDriver.hpp"
#include <cstdint>
#include <cstddef>

namespace M80::I2s
{
    class II2s;
}

namespace M81::RtosTask
{
    class IRtosTask;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M60::Audio
{
    class AudioDeviceDriver : public DeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        AudioDeviceDriver(
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        AudioDeviceDriver(
            const AudioDeviceDriver&) = delete;
        
        AudioDeviceDriver& operator=(
            const AudioDeviceDriver&) = delete;
        
        AudioDeviceDriver(AudioDeviceDriver&&) = delete;
        
        AudioDeviceDriver& operator=(
            AudioDeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~AudioDeviceDriver() override;

        M80::I2s::II2s& GetI2s();
        
        void SetI2s(
            M80::I2s::II2s& i2s);

        void SetConfiguration(
            uint8_t port,
            uint8_t bclkPin,
            uint8_t wsPin,
            uint8_t dinPin,
            uint8_t doutPin,
            uint32_t sampleRate,
            uint16_t bitsPerSample,
            uint8_t channels);

        void SetRtosTask(
            M81::RtosTask::IRtosTask& rtosTask);

        void Initialize() override;

        size_t Read(
            void* buffer,
            size_t length,
            uint32_t timeoutInMs);

        size_t Write(
            const void* buffer,
            size_t length,
            uint32_t timeoutInMs);

        bool Start();

        bool Stop();

    private:
        uint8_t _port;
        
        uint8_t _bclkPin;
        
        uint8_t _wsPin;
        
        uint8_t _dinPin;
        
        uint8_t _doutPin;
        
        uint32_t _sampleRate;
        
        uint16_t _bitsPerSample;
        
        uint8_t _channels;

        M80::I2s::II2s* _i2s;
        
        M81::RtosTask::IRtosTask* _rtosTask;
    };
}