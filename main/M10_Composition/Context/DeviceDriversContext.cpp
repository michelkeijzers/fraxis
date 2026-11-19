#include "DeviceDriversContext.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include <memory>

DeviceDriversContext::DeviceDriversContext(
    M90::Assert::IAssert& assert)
:
    _i2cDeviceDriver(nullptr),
    _spiDeviceDriver(nullptr),
    _lcd2004DeviceDriver(nullptr),
    _mcp23017DeviceDriver(nullptr),
    _tm1637DeviceDriverCentralPanel(nullptr),
    _tm1637DeviceDriverPlayer1(nullptr),
    _tm1637DeviceDriverPlayer2(nullptr),
    _ws28xxDeviceDriver(nullptr),
    _microSdCardDeviceDriver(nullptr),
    _audioDeviceDriver(nullptr),
    _inmp1441DeviceDriver(nullptr),
    _max53987aDeviceDriver(nullptr),
    _buzzerDeviceDriver(nullptr),
    _assert(assert)
{
    // No actions required.
}

void DeviceDriversContext::SetI2cDeviceDriver(
    std::unique_ptr<M60::I2c::I2cDeviceDriver> i2cDeviceDriver)
{
    _i2cDeviceDriver = std::move(i2cDeviceDriver);
}

void DeviceDriversContext::SetSpiDeviceDriver(
    std::unique_ptr<M60::Spi::SpiDeviceDriver> spiDeviceDriver)
{
    _spiDeviceDriver = std::move(spiDeviceDriver);
}

void DeviceDriversContext::SetLcd2004DeviceDriver(
    std::unique_ptr<M60::I2c::Lcd2004DeviceDriver> lcd2004DeviceDriver)
{
    _lcd2004DeviceDriver = std::move(lcd2004DeviceDriver);
}

void DeviceDriversContext::SetMcp23017DeviceDriver(
    std::unique_ptr<M60::I2c::Mcp23017DeviceDriver> mcp23017DeviceDriver)
{
    _mcp23017DeviceDriver = std::move(mcp23017DeviceDriver);
}

void DeviceDriversContext::SetTm1637CentralPanelDeviceDriver(
    std::unique_ptr<M60::I2c::Tm1637DeviceDriver> tm1637DeviceDriverCentralPanel)
{
    _tm1637DeviceDriverCentralPanel = std::move(tm1637DeviceDriverCentralPanel);
}

void DeviceDriversContext::SetTm1637Player1DeviceDriver(
    std::unique_ptr<M60::I2c::Tm1637DeviceDriver> tm1637DeviceDriverPlayer1)
{
    _tm1637DeviceDriverPlayer1 = std::move(tm1637DeviceDriverPlayer1);
}

void DeviceDriversContext::SetTm1637Player2DeviceDriver(
    std::unique_ptr<M60::I2c::Tm1637DeviceDriver> tm1637DeviceDriverPlayer2)
{
    _tm1637DeviceDriverPlayer2 = std::move(tm1637DeviceDriverPlayer2);
}

void DeviceDriversContext::SetWs28xxDeviceDriver(
    std::unique_ptr<M60::Ws28xx::Ws28xxDeviceDriver> ws28xxDeviceDriver)
{
    _ws28xxDeviceDriver = std::move(ws28xxDeviceDriver);
}

void DeviceDriversContext::SetMicroSdCardDeviceDriver(
    std::unique_ptr<M60::Spi::MicroSdCardDeviceDriver> microSdCardDeviceDriver)
{
    _microSdCardDeviceDriver = std::move(microSdCardDeviceDriver);
}

void DeviceDriversContext::SetAudioDeviceDriver(
    std::unique_ptr<M60::Audio::AudioDeviceDriver> audioDeviceDriver)
{
    _audioDeviceDriver = std::move(audioDeviceDriver);
}

void DeviceDriversContext::SetInmp1441DeviceDriver(
    std::unique_ptr<M60::Audio::Inmp1441DeviceDriver> inmp1441DeviceDriver)
{
    _inmp1441DeviceDriver = std::move(inmp1441DeviceDriver);
}

void DeviceDriversContext::SetMax53987aDeviceDriver(
    std::unique_ptr<M60::Audio::Max53987aDeviceDriver> max53987aDeviceDriver)
{
    _max53987aDeviceDriver = std::move(max53987aDeviceDriver);
}

void DeviceDriversContext::SetBuzzerDeviceDriver(
    std::unique_ptr<M60::Audio::BuzzerDeviceDriver> buzzerDeviceDriver)
{
    _buzzerDeviceDriver = std::move(buzzerDeviceDriver);
}

M60::I2c::I2cDeviceDriver& DeviceDriversContext::GetI2cDeviceDriver()
{
    return *_i2cDeviceDriver;
}

M60::Spi::SpiDeviceDriver& DeviceDriversContext::GetSpiDeviceDriver()
{
    return *_spiDeviceDriver;
}

M60::I2c::Lcd2004DeviceDriver& DeviceDriversContext::GetLcd2004DeviceDriver()
{
    return *_lcd2004DeviceDriver;
}

M60::I2c::Mcp23017DeviceDriver& DeviceDriversContext::GetMcp23017DeviceDriver()
{
    return *_mcp23017DeviceDriver;
}

M60::I2c::Tm1637DeviceDriver& DeviceDriversContext::GetTm1637DeviceDriverCentralPanel()
{
    return *_tm1637DeviceDriverCentralPanel;
}

M60::I2c::Tm1637DeviceDriver& DeviceDriversContext::GetTm1637DeviceDriverPlayer1()
{
    return *_tm1637DeviceDriverPlayer1;
}   

M60::I2c::Tm1637DeviceDriver& DeviceDriversContext::GetTm1637DeviceDriverPlayer2()
{
    return *_tm1637DeviceDriverPlayer2;
}

M60::Ws28xx::Ws28xxDeviceDriver& DeviceDriversContext::GetWs28xxDeviceDriver()
{
    return *_ws28xxDeviceDriver;
}

M60::Spi::MicroSdCardDeviceDriver& DeviceDriversContext::GetMicroSdCardDeviceDriver()
{
    return *_microSdCardDeviceDriver;
}

M60::Audio::AudioDeviceDriver& DeviceDriversContext::GetAudioDeviceDriver()
{
    return *_audioDeviceDriver;
}

M60::Audio::Inmp1441DeviceDriver& DeviceDriversContext::GetInmp1441DeviceDriver()
{
    return *_inmp1441DeviceDriver;
}

M60::Audio::Max53987aDeviceDriver& DeviceDriversContext::GetMax53987aDeviceDriver()
{
    return *_max53987aDeviceDriver;
}

M60::Audio::BuzzerDeviceDriver& DeviceDriversContext::GetBuzzerDeviceDriver()
{
    return *_buzzerDeviceDriver;
}
