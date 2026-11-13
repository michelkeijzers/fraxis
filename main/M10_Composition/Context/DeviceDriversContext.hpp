#pragma once

#include <memory>
#include "../../M30_Messages/Types.hpp"
#include "../../M60_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/Spi/SpiDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2c/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2c/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2c/Tm1637/Tm1637DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/Spi/MicroSdCard/MicroSdCardDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/Audio/AudioDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/Audio/Microphone/Inmp1441DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/Audio/Dac/Max53987aDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/Audio/Buzzer/BuzzerDeviceDriver.hpp"

class DeviceDriversContext
{
public:
    DeviceDriversContext();

    DeviceDriversContext(
        const DeviceDriversContext&) = delete;

    DeviceDriversContext& operator=(
        const DeviceDriversContext&) = delete;

    DeviceDriversContext(
        DeviceDriversContext&&) = delete;

    DeviceDriversContext& operator=(
        DeviceDriversContext&&) = delete;

    ~DeviceDriversContext() = default;

    void Set(
        std::unique_ptr<M60::I2c::I2cDeviceDriver> i2cDeviceDriver,
        std::unique_ptr<M60::Spi::SpiDeviceDriver> spiDeviceDriver,
        std::unique_ptr<M60::Lcd2004::Lcd2004DeviceDriver> lcd2004DeviceDriver,
        std::unique_ptr<M60::Mcp23017::Mcp23017DeviceDriver> mcp23017DeviceDriver,
        std::unique_ptr<M60::I2c::Tm1637DeviceDriver> tm1637DeviceDriverCentralPanel,
        std::unique_ptr<M60::I2c::Tm1637DeviceDriver> tm1637DeviceDriverPlayer1,
        std::unique_ptr<M60::I2c::Tm1637DeviceDriver> tm1637DeviceDriverPlayer2,
        std::unique_ptr<M60::Ws28xx::Ws28xxDeviceDriver> ws28xxDeviceDriver,
        std::unique_ptr<M60::Spi::MicroSdCardDeviceDriver> microSdCardDeviceDriver,
        std::unique_ptr<M60::Audio::AudioDeviceDriver> audioDeviceDriver,
        std::unique_ptr<M60::Audio::Inmp1441DeviceDriver> microphoneDeviceDriver,
        std::unique_ptr<M60::Audio::Max53987aDeviceDriver> dacDeviceDriver,
        std::unique_ptr<M60::Audio::BuzzerDeviceDriver> buzzerDeviceDriver
    );

    M60::I2c::I2cDeviceDriver& GetI2cDeviceDriver();
    M60::Spi::SpiDeviceDriver& GetSpiDeviceDriver();
    M60::Lcd2004::Lcd2004DeviceDriver& GetLcd2004DeviceDriver();
    M60::Mcp23017::Mcp23017DeviceDriver& GetMcp23017DeviceDriver();
    M60::I2c::Tm1637DeviceDriver& GetTm1637DeviceDriverCentralPanel();
    M60::I2c::Tm1637DeviceDriver& GetTm1637DeviceDriverPlayer1();
    M60::I2c::Tm1637DeviceDriver& GetTm1637DeviceDriverPlayer2();
    M60::I2c::Tm1637DeviceDriver& GetTm1637DeviceDriverId(
        Types::ETm1637Id tm1637id);
    M60::Ws28xx::Ws28xxDeviceDriver& GetWs28xxDeviceDriver();
    M60::Spi::MicroSdCardDeviceDriver& GetMicroSdCardDeviceDriver();
    M60::Audio::AudioDeviceDriver& GetAudioDeviceDriver();
    M60::Audio::Inmp1441DeviceDriver& GetMicrophoneDeviceDriver();
    M60::Audio::Max53987aDeviceDriver& GetDacDeviceDriver();
    M60::Audio::BuzzerDeviceDriver& GetBuzzerDeviceDriver();

private:
    std::unique_ptr<M60::I2c::I2cDeviceDriver> _i2cDeviceDriver;
    std::unique_ptr<M60::Spi::SpiDeviceDriver> _spiDeviceDriver;
    std::unique_ptr<M60::Lcd2004::Lcd2004DeviceDriver> _lcd2004DeviceDriver;
    std::unique_ptr<M60::Mcp23017::Mcp23017DeviceDriver> _mcp23017DeviceDriver;
    std::unique_ptr<M60::I2c::Tm1637DeviceDriver> _tm1637DeviceDriverCentralPanel;
    std::unique_ptr<M60::I2c::Tm1637DeviceDriver> _tm1637DeviceDriverPlayer1;
    std::unique_ptr<M60::I2c::Tm1637DeviceDriver> _tm1637DeviceDriverPlayer2;
    std::unique_ptr<M60::Ws28xx::Ws28xxDeviceDriver> _ws28xxDeviceDriver;
    std::unique_ptr<M60::Spi::MicroSdCardDeviceDriver> _microSdCardDeviceDriver;
    std::unique_ptr<M60::Audio::AudioDeviceDriver> _audioDeviceDriver;
    std::unique_ptr<M60::Audio::Inmp1441DeviceDriver> _microphoneDeviceDriver;
    std::unique_ptr<M60::Audio::Max53987aDeviceDriver> _dacDeviceDriver;
    std::unique_ptr<M60::Audio::BuzzerDeviceDriver> _buzzerDeviceDriver;
};
