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
    _ws2812Rmt(nullptr),
    _ws28xxDeviceDriver(nullptr),
    _microSdCardDeviceDriver(nullptr),
    _i2sDeviceDriver(nullptr),
    _inmp1441DeviceDriver(nullptr),
    _max53987aDeviceDriver(nullptr),
    _passiveBuzzerDeviceDriver(nullptr),
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
    std::unique_ptr<M60::IDeviceDriver> spiDeviceDriver)
{
    auto* realDriver = static_cast<M60::Spi::SpiDeviceDriver*>(spiDeviceDriver.release());
    _spiDeviceDriver = std::unique_ptr<M60::Spi::SpiDeviceDriver>(realDriver);
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
    std::unique_ptr<M60::SevenSegmentsDisplays::Tm1637DeviceDriver> tm1637DeviceDriverCentralPanel)
{
    _tm1637DeviceDriverCentralPanel = std::move(tm1637DeviceDriverCentralPanel);
}

void DeviceDriversContext::SetTm1637Player1DeviceDriver(
    std::unique_ptr<M60::SevenSegmentsDisplays::Tm1637DeviceDriver> tm1637DeviceDriverPlayer1)
{
    _tm1637DeviceDriverPlayer1 = std::move(tm1637DeviceDriverPlayer1);
}

void DeviceDriversContext::SetTm1637Player2DeviceDriver(
    std::unique_ptr<M60::SevenSegmentsDisplays::Tm1637DeviceDriver> tm1637DeviceDriverPlayer2)
{
    _tm1637DeviceDriverPlayer2 = std::move(tm1637DeviceDriverPlayer2);
}

void DeviceDriversContext::SetWs2812Rmt(
    std::unique_ptr<M60::Ws28xx::IWs2812Rmt> ws2812Rmt)
{
    auto* realWs2812Rmt = static_cast<M60::Ws28xx::Ws2812Rmt*>(ws2812Rmt.release());
    _ws2812Rmt = std::unique_ptr<M60::Ws28xx::Ws2812Rmt>(realWs2812Rmt);
}

void DeviceDriversContext::SetWs28xxDeviceDriver(
    std::unique_ptr<M60::IDeviceDriver> ws28xxDeviceDriver)
{
    auto* realDriver = static_cast<M60::Ws28xx::Ws28xxDeviceDriver*>(ws28xxDeviceDriver.release());
    _ws28xxDeviceDriver = std::unique_ptr<M60::Ws28xx::Ws28xxDeviceDriver>(realDriver);
}

void DeviceDriversContext::SetMicroSdCardDeviceDriver(
    std::unique_ptr<M60::Spi::MicroSdCardDeviceDriver> microSdCardDeviceDriver)
{
    _microSdCardDeviceDriver = std::move(microSdCardDeviceDriver);
}

void DeviceDriversContext::SetI2sDeviceDriver(
    std::unique_ptr<M60::I2s::I2sDeviceDriver> i2sDeviceDriver)
{
    _i2sDeviceDriver = std::move(i2sDeviceDriver);
}

void DeviceDriversContext::SetInmp1441DeviceDriver(
    std::unique_ptr<M60::I2s::Inmp1441DeviceDriver> inmp1441DeviceDriver)
{
    _inmp1441DeviceDriver = std::move(inmp1441DeviceDriver);
}

void DeviceDriversContext::SetMax53987aDeviceDriver(
    std::unique_ptr<M60::I2s::Max53987aDeviceDriver> max53987aDeviceDriver)
{
    _max53987aDeviceDriver = std::move(max53987aDeviceDriver);
}

void DeviceDriversContext::SetPassiveBuzzerDeviceDriver(
    std::unique_ptr<M60::I2s::PassiveBuzzerDeviceDriver> passiveBuzzerDeviceDriver)
{
    _passiveBuzzerDeviceDriver = std::move(passiveBuzzerDeviceDriver);
}

M60::I2c::II2cDeviceDriver& DeviceDriversContext::GetI2cDeviceDriver()
{
    return *_i2cDeviceDriver;
}

M60::Spi::ISpiDeviceDriver& DeviceDriversContext::GetSpiDeviceDriver()
{
    return *_spiDeviceDriver;
}

M60::I2c::ILcd2004DeviceDriver& DeviceDriversContext::GetLcd2004DeviceDriver()
{
    return *_lcd2004DeviceDriver;
}

M60::I2c::IMcp23017DeviceDriver& DeviceDriversContext::GetMcp23017DeviceDriver()
{
    return *_mcp23017DeviceDriver;
}

M60::SevenSegmentsDisplays::ITm1637DeviceDriver&
DeviceDriversContext::GetSpecificTypedTm1637DeviceDriverCentralPanel()
{
    return *_tm1637DeviceDriverCentralPanel;
}

M60::IDeviceDriver& DeviceDriversContext::GetTm1637DeviceDriverCentralPanel()
{
    return *_tm1637DeviceDriverCentralPanel;
}

M60::SevenSegmentsDisplays::ITm1637DeviceDriver&
DeviceDriversContext::GetSpecificTypedTm1637DeviceDriverPlayer1()
{
    return *_tm1637DeviceDriverPlayer1;
}

M60::IDeviceDriver& DeviceDriversContext::GetTm1637DeviceDriverPlayer1()
{
    return *_tm1637DeviceDriverPlayer1;
}   

M60::SevenSegmentsDisplays::ITm1637DeviceDriver& 
    DeviceDriversContext::GetSpecificTypedTm1637DeviceDriverPlayer2()
{
    return *_tm1637DeviceDriverPlayer2;
}

M60::IDeviceDriver& DeviceDriversContext::GetTm1637DeviceDriverPlayer2()
{
    return *_tm1637DeviceDriverPlayer2;
}

M60::Ws28xx::IWs2812Rmt& DeviceDriversContext::GetWs2812Rmt()
{
    return *_ws2812Rmt;
}

M60::IDeviceDriver& DeviceDriversContext::GetWs28xxDeviceDriver()
{
    return *_ws28xxDeviceDriver;
}

M60::Ws28xx::IWs28xxDeviceDriver& DeviceDriversContext::GetSpecificTypedWs28xxDeviceDriver()
{
    return *_ws28xxDeviceDriver;
}

M60::Spi::MicroSdCardDeviceDriver& DeviceDriversContext::GetMicroSdCardDeviceDriver()
{
    return *_microSdCardDeviceDriver;
}

M60::I2s::I2sDeviceDriver& DeviceDriversContext::GetI2sDeviceDriver()
{
    return *_i2sDeviceDriver;
}

M60::I2s::Inmp1441DeviceDriver& DeviceDriversContext::GetInmp1441DeviceDriver()
{
    return *_inmp1441DeviceDriver;
}

M60::I2s::Max53987aDeviceDriver& DeviceDriversContext::GetMax53987aDeviceDriver()
{
    return *_max53987aDeviceDriver;
}

M60::I2s::PassiveBuzzerDeviceDriver& DeviceDriversContext::GetPassiveBuzzerDeviceDriver()
{
    return *_passiveBuzzerDeviceDriver;
}
