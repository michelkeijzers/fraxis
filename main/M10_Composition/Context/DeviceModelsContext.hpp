#pragma once

#include "../../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include <memory>

// Forward declarations of device models

namespace M50::I2c
{
    class ILcd2004DeviceModel;
    class Lcd2004DeviceModel;
    class IMcp23017DeviceModel;
    class Mcp23017DeviceModel;
}

namespace M50::SevenSegmentsDisplays
{
    class Tm1637DeviceModel;
}

namespace M50::Ws28xx
{
    class IWs28xxDeviceModel;
}

namespace M50::Spi
{
    class MicroSdCardDeviceModel;
}

namespace M50::I2s
{
    class I2sDeviceModel;
    class Inmp1441DeviceModel;
    class Max53987aDeviceModel;
}

namespace M50::PassiveBuzzer
{
    class PassiveBuzzerDeviceModel;
}

class DeviceModelsContext
{
public:
    // Do not make = default.
    DeviceModelsContext();

    DeviceModelsContext(
        const DeviceModelsContext&) = delete;

    DeviceModelsContext& operator=(
        const DeviceModelsContext&) = delete;

    DeviceModelsContext(
        DeviceModelsContext&&) = delete;

    DeviceModelsContext& operator=(
        DeviceModelsContext&&) = delete;

    // Do not make = default.
    ~DeviceModelsContext();

    void Set(
        std::unique_ptr<M50::I2c::Lcd2004DeviceModel> lcd2004DeviceModel,
        std::unique_ptr<M50::I2c::Mcp23017DeviceModel> mcp23017DeviceModel,
        std::unique_ptr<M50::SevenSegmentsDisplays::Tm1637DeviceModel> 
            tm1637DeviceModelCentralPanel,
        std::unique_ptr<M50::SevenSegmentsDisplays::Tm1637DeviceModel> 
            tm1637DeviceModelPlayer1,
        std::unique_ptr<M50::SevenSegmentsDisplays::Tm1637DeviceModel> 
            tm1637DeviceModelPlayer2,
        std::unique_ptr<M50::Ws28xx::Ws28xxDeviceModel> ws28xxDeviceModel,
        std::unique_ptr<M50::Spi::MicroSdCardDeviceModel> microSdCardDeviceModel,
        std::unique_ptr<M50::I2s::I2sDeviceModel> i2sDeviceModel,
        std::unique_ptr<M50::I2s::Inmp1441DeviceModel> inmp1441DeviceModel,
        std::unique_ptr<M50::I2s::Max53987aDeviceModel> max53987aDeviceModel,
        std::unique_ptr<M50::PassiveBuzzer::PassiveBuzzerDeviceModel> passiveBuzzerDeviceModel
    );

    M50::I2c::ILcd2004DeviceModel& GetSpecificTypedLcd2004DeviceModel();

    M50::IDeviceModel& GetLcd2004DeviceModel();

    M50::I2c::IMcp23017DeviceModel& GetSpecificTypedMcp23017DeviceModel();

    M50::IDeviceModel& GetMcp23017DeviceModel();

    M50::SevenSegmentsDisplays::Tm1637DeviceModel& GetTm1637DeviceModelCentralPanel();

    M50::SevenSegmentsDisplays::Tm1637DeviceModel& GetTm1637DeviceModelPlayer1();

    M50::SevenSegmentsDisplays::Tm1637DeviceModel& GetTm1637DeviceModelPlayer2();

    M50::Ws28xx::IWs28xxDeviceModel& GetSpecificTypedWs28xxDeviceModel();

    M50::IDeviceModel& GetWs28xxDeviceModel();

    M50::Spi::MicroSdCardDeviceModel& GetMicroSdCardDeviceModel();

    M50::I2s::I2sDeviceModel& GetI2sDeviceModel();

    M50::I2s::Inmp1441DeviceModel& GetInmp1441DeviceModel();

    M50::I2s::Max53987aDeviceModel& GetMax53987aDeviceModel();

    M50::PassiveBuzzer::PassiveBuzzerDeviceModel& GetPassiveBuzzerDeviceModel();

private:
    std::unique_ptr<M50::I2c::Lcd2004DeviceModel> _lcd2004DeviceModel;

    std::unique_ptr<M50::I2c::Mcp23017DeviceModel> _mcp23017DeviceModel;

    std::unique_ptr<M50::SevenSegmentsDisplays::Tm1637DeviceModel> _tm1637DeviceModelCentralPanel;

    std::unique_ptr<M50::SevenSegmentsDisplays::Tm1637DeviceModel> _tm1637DeviceModelPlayer1;

    std::unique_ptr<M50::SevenSegmentsDisplays::Tm1637DeviceModel> _tm1637DeviceModelPlayer2;

    std::unique_ptr<M50::Ws28xx::Ws28xxDeviceModel> _ws28xxDeviceModel;

    std::unique_ptr<M50::Spi::MicroSdCardDeviceModel> _microSdCardDeviceModel;

    std::unique_ptr<M50::I2s::I2sDeviceModel> _i2sDeviceModel;

    std::unique_ptr<M50::I2s::Inmp1441DeviceModel> _inmp1441DeviceModel;

    std::unique_ptr<M50::I2s::Max53987aDeviceModel> _max53987aDeviceModel;

    std::unique_ptr<M50::PassiveBuzzer::PassiveBuzzerDeviceModel> _passiveBuzzerDeviceModel;
};
