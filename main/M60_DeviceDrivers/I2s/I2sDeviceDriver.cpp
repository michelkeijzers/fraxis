#include "I2sDeviceDriver.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include "../../M80_Services/I2s/II2sService.hpp"
#include "../../M30_Messages/Types.hpp"

namespace M60::I2s
{
    I2sDeviceDriver::I2sDeviceDriver(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities)
    : 
        DeviceDriver(assert, stringUtilities),
        _port(0),
        _bclkPin(0),
        _wsPin(0),
        _dinPin(0),
        _doutPin(0),
        _sampleRate(16000),
        _bitsPerSample(16),
        _channels(1),
        _i2s(nullptr),
        _rtosTask(nullptr)
    {
    }

    // Do not make =default because of unique_ptr needing complete (sub) types.
    I2sDeviceDriver::~I2sDeviceDriver() = default;

    void I2sDeviceDriver::SetConfiguration(
        uint8_t port,
        uint8_t bclkPin,
        uint8_t wsPin,
        uint8_t dinPin,
        uint8_t doutPin,
        uint32_t sampleRate,
        uint16_t bitsPerSample,
        uint8_t channels)
    {
        _port = port;
        _bclkPin = bclkPin;
        _wsPin = wsPin;
        _dinPin = dinPin;
        _doutPin = doutPin;
        _sampleRate = sampleRate;
        _bitsPerSample = bitsPerSample;
        _channels = channels;
    }

    M80::I2s::II2sService& I2sDeviceDriver::GetI2s()
    {
        return *_i2s;
    }

    void I2sDeviceDriver::SetI2s(
        M80::I2s::II2sService& i2s)
    {
        _i2s = &i2s;
    }

    void I2sDeviceDriver::SetRtosTask(
        M81::RtosTask::IRtosTask& rtosTask)
    {
        _rtosTask = &rtosTask;
    }

    void I2sDeviceDriver::Initialize()
    {
        GetAssert().IsTrue(
            Types::ETaskId::I2sTask,
            GetI2s().ParamConfig(_port, _bclkPin, _wsPin, _dinPin, _doutPin, _sampleRate, _bitsPerSample, _channels),
            "Failed to param config");
        GetAssert().IsTrue(
            Types::ETaskId::I2sTask,
            GetI2s().DriverInstall(_port),
            "Failed to install I2S driver");
        MarkInitialized();
    }

    size_t I2sDeviceDriver::Read(
        void* buffer,
        size_t length,
        uint32_t timeoutInMs)
    {
        GetAssert().IsTrue(Types::ETaskId::I2sTask, IsInitialized());
        return GetI2s().Read(_port, buffer, length, timeoutInMs);
    }

    size_t I2sDeviceDriver::Write(
        const void* buffer,
        size_t length,
        uint32_t timeoutInMs)
    {
        GetAssert().IsTrue(Types::ETaskId::I2sTask, IsInitialized());
        return GetI2s().Write(_port, buffer, length, timeoutInMs);
    }

    bool I2sDeviceDriver::Start()
    {
        return GetI2s().Start(_port);
    }

    bool I2sDeviceDriver::Stop()
    {
        return GetI2s().Stop(_port);
    }
}