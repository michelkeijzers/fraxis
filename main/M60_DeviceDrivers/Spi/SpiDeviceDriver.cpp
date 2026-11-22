#include "SpiDeviceDriver.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include "../../M80_Services/Spi/ISpi.hpp"

namespace M60::Spi
{
    SpiDeviceDriver::SpiDeviceDriver(
        uint8_t port,
        uint8_t mosiPin,
        uint8_t misoPin,
        uint8_t sclkPin,
        uint32_t frequency,
        M80::Spi::ISpi& spi,
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities)
    :
        DeviceDriver(assert, stringUtilities),
        _port(port),
        _mosiPin(mosiPin),
        _misoPin(misoPin),
        _sclkPin(sclkPin),
        _frequency(frequency),
        _spi(spi)
    {
        AssertValidPort(port);
    }

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    SpiDeviceDriver::~SpiDeviceDriver() = default;

    M80::Spi::ISpi& SpiDeviceDriver::GetSpi()
    {
        return _spi;
    }

    void SpiDeviceDriver::AssertValidPort(
        uint8_t port)
    {
        GetAssert().IsTrue(
            Types::ETaskId::SpiTask, GetSpi().IsValidPort(port), "SPI Port should be xxx");
        // NOSONAR TODO SPI
    }

    void SpiDeviceDriver::Initialize()
    {
        //_csPin = -1; // NOSONAR TODO SPI
        GetAssert().IsTrue(
            Types::ETaskId::SpiTask,
            GetSpi().ParamConfig(_port, _mosiPin, _misoPin, _sclkPin, _frequency),
            "Failed to param config");
        GetAssert().IsTrue(
            Types::ETaskId::SpiTask,
            GetSpi().DriverInstall(_port),
            "Failed to install SPI driver");

        MarkInitialized();
    }

    // NOSONAR TODO SPI
    // void SpiDeviceDriver::Write(
    //     uint8_t deviceAddress, 
    //     const uint8_t* data, 
    //     size_t length)
    // {
    //     Assert::IsTrue(
    //         Types::ETaskId::SpiTask, IsInitialized());
    //     Assert::IsTrue(
    //         Types::ETaskId::SpiTask, 
    //         //GetI2c().MasterWriteToDevice(_port, deviceAddress, data, length, 1000), 
    //         "Failed to write to device");
    // }
    //
    // void SpiDeviceDriver::Read(
    //     uint8_t deviceAddress,
    //     uint8_t* data,
    //     size_t length)
    // {
    //     Assert::IsTrue(
    //         Types::ETaskId::I2cTask, IsInitialized());
    //     Assert::IsTrue(
    //         Types::ETaskId::I2cTask, 
    //         GetI2c().MasterReadFromDevice(_port, deviceAddress, data, length, 1000), 
    //         "Failed to read from device");
    // }
}
