#pragma once

#include <memory>

#include "../../M30_Messages/Types.hpp"
#include "../../M60_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/Spi/SpiDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2c/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2c/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/SevenSegmentsDisplays/Tm1637DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/Ws28xx/Ws2812Rmt.hpp"
#include "../../M60_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/Spi/MicroSdCard/MicroSdCardDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2s/I2sDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2s/Inmp1441/Inmp1441DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2s/Max53987a/Max53987aDeviceDriver.hpp"
#include "../../M60_DeviceDrivers/PassiveBuzzer/PassiveBuzzerDeviceDriver.hpp"


namespace M60::I2s
{
    class PAssiveBuzzerDeviceDriver;
}

namespace M60
{
    class IDeviceDriver;

    namespace I2c
    {
        class II2cDeviceDriver;
        class IMcp23017DeviceDriver;
        class ILcd2004DeviceDriver;
    }

    namespace Spi
    {
        class ISpiDeviceDriver;
    }

    namespace Ws28xx
    {
        class IWs2812Rmt;
    }
}

namespace M90::Assert
{
    class IAssert;
}

class DeviceDriversContext
{
public:
    explicit DeviceDriversContext(
        M90::Assert::IAssert& assert);

    DeviceDriversContext(
        const DeviceDriversContext&) = delete;

    DeviceDriversContext& operator=(
        const DeviceDriversContext&) = delete;

    DeviceDriversContext(
        DeviceDriversContext&&) = delete;

    DeviceDriversContext& operator=(
        DeviceDriversContext&&) = delete;

    ~DeviceDriversContext() = default;

    void SetI2cDeviceDriver(
        std::unique_ptr<M60::I2c::I2cDeviceDriver> i2cDeviceDriver);

    void SetSpiDeviceDriver(
        std::unique_ptr<M60::Spi::SpiDeviceDriver> spiDeviceDriver);

    void SetLcd2004DeviceDriver(
        std::unique_ptr<M60::I2c::Lcd2004DeviceDriver> lcd2004DeviceDriver);

    void SetMcp23017DeviceDriver(
        std::unique_ptr<M60::I2c::Mcp23017DeviceDriver> mcp23017DeviceDriver);

    void SetTm1637CentralPanelDeviceDriver(
        std::unique_ptr<M60::SevenSegmentsDisplays::Tm1637DeviceDriver> 
            tm1637DeviceDriverCentralPanel);

    void SetTm1637Player1DeviceDriver(
        std::unique_ptr<M60::SevenSegmentsDisplays::Tm1637DeviceDriver> tm1637DeviceDriverPlayer1);

    void SetTm1637Player2DeviceDriver(
        std::unique_ptr<M60::SevenSegmentsDisplays::Tm1637DeviceDriver> tm1637DeviceDriverPlayer2);

    void SetWs2812Rmt(
        std::unique_ptr<M60::Ws28xx::IWs2812Rmt> ws2812Rmt);

    void SetWs28xxDeviceDriver(
        std::unique_ptr<M60::Ws28xx::Ws28xxDeviceDriver> ws28xxDeviceDriver);

    void SetMicroSdCardDeviceDriver(
        std::unique_ptr<M60::Spi::MicroSdCardDeviceDriver> microSdCardDeviceDriver);

    void SetI2sDeviceDriver(
        std::unique_ptr<M60::I2s::I2sDeviceDriver> i2sDeviceDriver);
    
    void SetInmp1441DeviceDriver(
        std::unique_ptr<M60::I2s::Inmp1441DeviceDriver> inmp1441DeviceDriver);

    void SetMax53987aDeviceDriver(
        std::unique_ptr<M60::I2s::Max53987aDeviceDriver> max53987aDeviceDriver);

    void SetPassiveBuzzerDeviceDriver(
        std::unique_ptr<M60::PassiveBuzzer::PassiveBuzzerDeviceDriver> passiveBuzzerDeviceDriver);
    
    M60::I2c::II2cDeviceDriver& GetI2cTypedI2cDeviceDriver();

    M60::IDeviceDriver& GetI2cDeviceDriver();

    M60::Spi::ISpiDeviceDriver& GetSpiTypedSpiDeviceDriver();

    M60::IDeviceDriver& GetSpiDeviceDriver();

    M60::I2c::ILcd2004DeviceDriver& GetSpecificTypedLcd2004DeviceDriver();

    M60::IDeviceDriver& GetLcd2004DeviceDriver();

    M60::I2c::IMcp23017DeviceDriver& GetSpecificTypedMcp23017DeviceDriver();

    M60::IDeviceDriver& GetMcp23017DeviceDriver();

    M60::SevenSegmentsDisplays::ITm1637DeviceDriver&
        GetSpecificTypedTm1637DeviceDriverCentralPanel();


    M60::IDeviceDriver& GetTm1637DeviceDriverCentralPanel();

    M60::SevenSegmentsDisplays::ITm1637DeviceDriver&
        GetSpecificTypedTm1637DeviceDriverPlayer1();

    M60::IDeviceDriver& GetTm1637DeviceDriverPlayer1();

    M60::SevenSegmentsDisplays::ITm1637DeviceDriver&
        GetSpecificTypedTm1637DeviceDriverPlayer2();

    M60::IDeviceDriver& GetTm1637DeviceDriverPlayer2();
    
    M60::IDeviceDriver& GetTm1637DeviceDriverId(
        Types::ETm1637Id tm1637id);
    
    M60::Ws28xx::IWs2812Rmt& GetWs2812Rmt();

    M60::Ws28xx::IWs28xxDeviceDriver& GetSpecificTypedWs28xxDeviceDriver();

    M60::IDeviceDriver& GetWs28xxDeviceDriver();
    
    M60::Spi::IMicroSdCardDeviceDriver& GetSpecificTypedMicroSdCardDeviceDriver();
    
    M60::IDeviceDriver& GetMicroSdCardDeviceDriver();

    M60::I2s::I2sDeviceDriver& GetSpecificTypedI2sDeviceDriver();

    M60::I2s::II2sDeviceDriver& GetI2sTypedI2sDeviceDriver();

    M60::IDeviceDriver& GetI2sDeviceDriver();
    
    M60::I2s::IInmp1441DeviceDriver& GetSpecificTypedInmp1441DeviceDriver();

    M60::I2s::II2sDeviceDriver& GetI2sTypedInmp1441DeviceDriver();

    M60::IDeviceDriver& GetInmp1441DeviceDriver();
    
    M60::I2s::IMax53987aDeviceDriver& GetSpecificTypedMax53987aDeviceDriver();

    M60::I2s::II2sDeviceDriver& GetI2sTypedMax53987aDeviceDriver();

    M60::IDeviceDriver& GetMax53987aDeviceDriver();
    
    M60::PassiveBuzzer::IPassiveBuzzerDeviceDriver& GetSpecificTypedPassiveBuzzerDeviceDriver();

    M60::IDeviceDriver& GetPassiveBuzzerDeviceDriver();

private:
    std::unique_ptr<M60::I2c::I2cDeviceDriver> _i2cDeviceDriver;

    std::unique_ptr<M60::Spi::SpiDeviceDriver> _spiDeviceDriver;

    std::unique_ptr<M60::I2c::Lcd2004DeviceDriver> _lcd2004DeviceDriver;

    std::unique_ptr<M60::I2c::Mcp23017DeviceDriver> _mcp23017DeviceDriver;

    std::unique_ptr<M60::SevenSegmentsDisplays::Tm1637DeviceDriver> _tm1637DeviceDriverCentralPanel;

    std::unique_ptr<M60::SevenSegmentsDisplays::Tm1637DeviceDriver> _tm1637DeviceDriverPlayer1;

    std::unique_ptr<M60::SevenSegmentsDisplays::Tm1637DeviceDriver> _tm1637DeviceDriverPlayer2;

    std::unique_ptr<M60::Ws28xx::Ws2812Rmt> _ws2812Rmt;

    std::unique_ptr<M60::Ws28xx::Ws28xxDeviceDriver> _ws28xxDeviceDriver;

    std::unique_ptr<M60::Spi::MicroSdCardDeviceDriver> _microSdCardDeviceDriver;

    std::unique_ptr<M60::I2s::I2sDeviceDriver> _i2sDeviceDriver;

    std::unique_ptr<M60::I2s::Inmp1441DeviceDriver> _inmp1441DeviceDriver;

    std::unique_ptr<M60::I2s::Max53987aDeviceDriver> _max53987aDeviceDriver;

    std::unique_ptr<M60::PassiveBuzzer::PassiveBuzzerDeviceDriver> _passiveBuzzerDeviceDriver;

    M90::Assert::IAssert &_assert;
};
