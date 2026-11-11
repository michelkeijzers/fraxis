#include "I2cDeviceDriver.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M80_Services/I2c/I2c.hpp"

#ifdef ESP_PLATFORM
#include "esp_err.h"
#else
#include "../../M80_Services/WindowsEspErr.hpp"
#endif

I2cDeviceDriver::I2cDeviceDriver()
: 
    _port(0),
    _sdaPin(0), 
    _sclPin(0), 
    _frequency(0),
    _i2c(nullptr)
{
}

// Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
I2cDeviceDriver::~I2cDeviceDriver() = default;

void I2cDeviceDriver::SetConfiguration(
    uint8_t port, 
    uint8_t sdaPin, 
    uint8_t sclPin, 
    uint32_t frequency)
{
    AssertValidPort(port);
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        frequency == 100'000 || frequency == 400'000, 
        "i2c Frequency should be 100 or 400 KHz");

    _port = port;
    _sdaPin = sdaPin;
    _sclPin = sclPin;
    _frequency = frequency;
}

I2c& I2cDeviceDriver::GetI2c()
{
    return *_i2c;
}

void I2cDeviceDriver::SetI2c(
    I2c& i2c)
{
    _i2c = &i2c;
}

void I2cDeviceDriver::AssertValidPort(
    uint8_t port)
{
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().IsValidPort(port), 
        "i2c Port should be I2C_NUM_0 or I2C_NUM_1");
}

void I2cDeviceDriver::Initialize()
{
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().ParamConfig(_port, _sdaPin, _sclPin, _frequency), 
        ESP_OK,
        "Failed to param config");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().DriverInstall(_port), 
        ESP_OK,
        "Failed to install I2C driver");
    MarkInitialized();
}
    
void I2cDeviceDriver::Write(
    uint8_t deviceAddress, 
    const uint8_t* data, 
    size_t length)
{
    Assert::IsTrue(
        Types::ETaskId::I2cTask, IsInitialized());
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteToDevice(
            _port, deviceAddress, data, length, 1000), 
        ESP_OK,
        "Failed to write to device");
}

void I2cDeviceDriver::Read(
    uint8_t deviceAddress,
    uint8_t* data,
    size_t length)
{
    Assert::IsTrue(
        Types::ETaskId::I2cTask, IsInitialized());
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterReadFromDevice(_port, deviceAddress, data, length, 1000), 
        ESP_OK,
        "Failed to read from device");
}

uint8_t I2cDeviceDriver::ReadRegister(
    uint8_t deviceAddress, 
    uint8_t registerAddress)
{
    Assert::IsTrue(Types::ETaskId::I2cTask, IsInitialized());

    uint8_t value = 0;
    void* cmd = GetI2c().CmdLinkCreate();
    Assert::IsNotNullptr(Types::ETaskId::I2cTask, cmd, "CmdLinkCreate");

    // Write register address
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStart(cmd), 
        ESP_OK, 
        "Failed master start");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress), 
        ESP_OK,
        "Failed to write device address");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteRegisterAddress(cmd, registerAddress),
        ESP_OK,
        "Failed to write register address");

    // Read one byte
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStart(cmd), 
        ESP_OK,
        "Failed master start 2");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress), 
        ESP_OK,
        "Failed to write device address 2");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterReadByte(cmd, &value),
        ESP_OK,
        "Failed to read value");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStop(cmd), 
        ESP_OK,
        "Failed master stop");

    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterCmdBegin(_port, cmd, 10),
        ESP_OK,
        "Failed to master cmd begin");
    GetI2c().CmdLinkDelete(cmd);

    return value;
}

void I2cDeviceDriver::ReadRegister(
    uint8_t deviceAddress, 
    uint8_t registerAddress,
    uint8_t* data,
    size_t length)
{
    Assert::IsTrue(Types::ETaskId::I2cTask, IsInitialized());

    void* cmd = GetI2c().CmdLinkCreate();
    Assert::IsNotNullptr(Types::ETaskId::I2cTask, cmd, "CmdLinkCreate");

    // Write register address
    Assert::Equals(Types::ETaskId::I2cTask, 
        GetI2c().MasterStart(cmd), 
        ESP_OK,
        "Failed master start");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress), 
        ESP_OK,
        "Failed to write device address");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteRegisterAddress(cmd, registerAddress), 
        ESP_OK,
        "Failed to write register address");
    
    // Read data
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStart(cmd), 
        ESP_OK,
        "Failed master start 2");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress), 
        ESP_OK,
        "Failed to write device address 2");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterRead(cmd, data, length), 
        ESP_OK,
        "Failed to read value");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStop(cmd), 
        ESP_OK,
        "Failed master stop");
    
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterCmdBegin(_port, cmd, 10), 
        ESP_OK,
        "Failed to master cmd begin");
    GetI2c().CmdLinkDelete(cmd);
}

void I2cDeviceDriver::WriteRegister(
    uint8_t deviceAddress,
    uint8_t registerAddress,
    uint8_t value)
{
    Assert::IsTrue(Types::ETaskId::I2cTask, IsInitialized());

    void* cmd = GetI2c().CmdLinkCreate();
    Assert::IsNotNullptr(Types::ETaskId::I2cTask, cmd, "CmdLinkCreate");

    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStart(cmd), 
        ESP_OK,
        "Failed master start 2");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress), 
        ESP_OK,
        "Failed to write device address 2");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteRegisterAddress(cmd, registerAddress), 
        ESP_OK,
        "Failed to write register address 2");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteByte(cmd, value), 
        ESP_OK,
        "Failed to write value");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStop(cmd), 
        ESP_OK,
        "Failed master stop");

    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterCmdBegin(_port, cmd, 10), 
        ESP_OK,
        "Failed to master cmd begin");
    GetI2c().CmdLinkDelete(cmd);
}

void I2cDeviceDriver::WriteRegister(
    uint8_t deviceAddress,
    uint8_t registerAddress,
    const uint8_t* data,
    size_t length)
{
    Assert::IsTrue(Types::ETaskId::I2cTask, IsInitialized());

    void* cmd = GetI2c().CmdLinkCreate();
    Assert::IsNotNullptr(Types::ETaskId::I2cTask, cmd, "CmdLinkCreate");

    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStart(cmd), 
        ESP_OK,
        "Failed master start 2");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress),
        ESP_OK,
        "Failed to write device address 2");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteRegisterAddress(cmd, registerAddress), 
        ESP_OK,
        "Failed to write register address 2");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWrite(cmd, data, length), 
        ESP_OK,
        "Failed to write");
    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStop(cmd),
        ESP_OK,
        "Failed master stop");

    Assert::Equals(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterCmdBegin(_port, cmd, 50), 
        ESP_OK,
        "Failed to master cmd begin");
    GetI2c().CmdLinkDelete(cmd);
}
