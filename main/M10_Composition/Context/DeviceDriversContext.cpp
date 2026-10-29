#include "DeviceDriversContext.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include <memory>

DeviceDriversContext::DeviceDriversContext()
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
    _microphoneDeviceDriver(nullptr),
    _dacDeviceDriver(nullptr),
    _buzzerDeviceDriver(nullptr)
{
}

void DeviceDriversContext::Set( // NOSONAR S107: >= 7 parameters
    std::unique_ptr<I2cDeviceDriver> i2cDeviceDriver,
    std::unique_ptr<SpiDeviceDriver> spiDeviceDriver,
    std::unique_ptr<Lcd2004DeviceDriver> lcd2004DeviceDriver,
    std::unique_ptr<Mcp23017DeviceDriver> mcp23017DeviceDriver,
    std::unique_ptr<Tm1637DeviceDriver> tm1637DeviceDriverCentralPanel,
    std::unique_ptr<Tm1637DeviceDriver> tm1637DeviceDriverPlayer1,
    std::unique_ptr<Tm1637DeviceDriver> tm1637DeviceDriverPlayer2,
    std::unique_ptr<Ws28xxDeviceDriver> ws28xxDeviceDriver,
    std::unique_ptr<MicroSdCardDeviceDriver> microSdCardDeviceDriver,
    std::unique_ptr<AudioDeviceDriver> audioDeviceDriver,
    std::unique_ptr<Inmp1441DeviceDriver> microphoneDeviceDriver,
    std::unique_ptr<Max53987aDeviceDriver> dacDeviceDriver,
    std::unique_ptr<BuzzerDeviceDriver> buzzerDeviceDriver)
{
    _i2cDeviceDriver = std::move(i2cDeviceDriver);
    _spiDeviceDriver = std::move(spiDeviceDriver);
    _lcd2004DeviceDriver = std::move(lcd2004DeviceDriver);
    _mcp23017DeviceDriver = std::move(mcp23017DeviceDriver);
    _tm1637DeviceDriverCentralPanel = std::move(tm1637DeviceDriverCentralPanel);
    _tm1637DeviceDriverPlayer1 = std::move(tm1637DeviceDriverPlayer1);
    _tm1637DeviceDriverPlayer2 = std::move(tm1637DeviceDriverPlayer2);
    _ws28xxDeviceDriver = std::move(ws28xxDeviceDriver);
    _microSdCardDeviceDriver = std::move(microSdCardDeviceDriver);
    _audioDeviceDriver = std::move(audioDeviceDriver);
    _microphoneDeviceDriver = std::move(microphoneDeviceDriver);
    _dacDeviceDriver = std::move(dacDeviceDriver);
    _buzzerDeviceDriver = std::move(buzzerDeviceDriver);
}

I2cDeviceDriver& DeviceDriversContext::GetI2cDeviceDriver() 
{
    return *_i2cDeviceDriver;
}

SpiDeviceDriver& DeviceDriversContext::GetSpiDeviceDriver() 
{
    return *_spiDeviceDriver;
}

Lcd2004DeviceDriver& DeviceDriversContext::GetLcd2004DeviceDriver() 
{
    return *_lcd2004DeviceDriver;
}

Mcp23017DeviceDriver& DeviceDriversContext::GetMcp23017DeviceDriver() 
{
    return *_mcp23017DeviceDriver;
}

Tm1637DeviceDriver& DeviceDriversContext::GetTm1637DeviceDriverCentralPanel() 
{
    return *_tm1637DeviceDriverCentralPanel;
}

Tm1637DeviceDriver& DeviceDriversContext::GetTm1637DeviceDriverPlayer1() 
{
    return *_tm1637DeviceDriverPlayer1;
}   

Tm1637DeviceDriver& DeviceDriversContext::GetTm1637DeviceDriverPlayer2() 
{
    return *_tm1637DeviceDriverPlayer2;
}

Tm1637DeviceDriver& DeviceDriversContext::GetTm1637DeviceDriverId(
    Types::ETm1637Id tm1637id)
{
    using enum Types::ETm1637Id;
    switch (tm1637id)
    {
        case CentralPanel: return *_tm1637DeviceDriverCentralPanel;
        case Player1:      return *_tm1637DeviceDriverPlayer1;
        case Player2:      return *_tm1637DeviceDriverPlayer2;
        default: 
            Assert::Fail(Types::ETaskId::System, "Illegal TM1637 ID"); 
    }
    return *_tm1637DeviceDriverCentralPanel; // Unreachable
}

Ws28xxDeviceDriver& DeviceDriversContext::GetWs28xxDeviceDriver() 
{
    return *_ws28xxDeviceDriver;
}

MicroSdCardDeviceDriver& DeviceDriversContext::GetMicroSdCardDeviceDriver() 
{
    return *_microSdCardDeviceDriver;
}

AudioDeviceDriver& DeviceDriversContext::GetAudioDeviceDriver()
{
    return *_audioDeviceDriver;
}

Inmp1441DeviceDriver& DeviceDriversContext::GetMicrophoneDeviceDriver()
{
    return *_microphoneDeviceDriver;
}

Max53987aDeviceDriver& DeviceDriversContext::GetDacDeviceDriver()
{
    return *_dacDeviceDriver;
}

BuzzerDeviceDriver& DeviceDriversContext::GetBuzzerDeviceDriver()
{
    return *_buzzerDeviceDriver;
}
