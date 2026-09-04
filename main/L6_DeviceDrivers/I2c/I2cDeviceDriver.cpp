#include "I2cDeviceDriver.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "../../L8_Services/I2c/I2c.hpp"

I2cDeviceDriver::I2cDeviceDriver()
    : _port(0), _sdaPin(0), _sclPin(0), _frequency(0), _i2c(nullptr)
{
}

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
    Assert::IsTrue(Types::ETaskId::I2cTask, GetI2c().IsValidPort(port), "i2c Port should be I2C_NUM_0 or I2C_NUM_1");
}

void I2cDeviceDriver::Initialize()
{
    Assert::IsTrue(
        Types::ETaskId::I2cTask, GetI2c().ParamConfig(_port, _sdaPin, _sclPin, _frequency), "Failed to param config");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, GetI2c().DriverInstall(_port), "Failed to install I2C driver");
    MarkInitialized();
}
    
void I2cDeviceDriver::Write(
    uint8_t deviceAddress, 
    const uint8_t* data, 
    size_t length)
{
    Assert::IsTrue(
        Types::ETaskId::I2cTask, IsInitialized());
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteToDevice(_port, deviceAddress, data, length, 1000), "Failed to write to device");
}

void I2cDeviceDriver::Read(
    uint8_t deviceAddress,
    uint8_t* data,
    size_t length)
{
    Assert::IsTrue(
        Types::ETaskId::I2cTask, IsInitialized());
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterReadFromDevice(_port, deviceAddress, data, length, 1000), "Failed to read from device");
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
    Assert::IsTrue(Types::ETaskId::I2cTask, GetI2c().MasterStart(cmd), "Failed master start");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress), 
        "Failed to write device address");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteRegisterAddress(cmd, registerAddress),
        "Failed to write register address");

    // Read one byte
    Assert::IsTrue(
        Types::ETaskId::I2cTask, GetI2c().MasterStart(cmd), 
        "Failed master start 2");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress), 
        "Failed to write device address 2");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterReadByte(cmd, &value),
         "Failed to read value");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStop(cmd), 
        "Failed master stop");

    Assert::IsTrue(
        Types::ETaskId::I2cTask, GetI2c().MasterCmdBegin(_port, cmd, 10),
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
    Assert::IsTrue(Types::ETaskId::I2cTask, GetI2c().MasterStart(cmd), 
        "Failed master start");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress), 
        "Failed to write device address");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteRegisterAddress(cmd, registerAddress), 
        "Failed to write register address");
    
    // Read data
    Assert::IsTrue(Types::ETaskId::I2cTask, GetI2c().MasterStart(cmd), "Failed master start 2");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress), 
        "Failed to write device address 2");
    Assert::IsTrue(Types::ETaskId::I2cTask, GetI2c().MasterRead(cmd, data, length), "Failed to read value");
    Assert::IsTrue(Types::ETaskId::I2cTask, GetI2c().MasterStop(cmd), "Failed master stop");
    
    Assert::IsTrue(Types::ETaskId::I2cTask, GetI2c().MasterCmdBegin(_port, cmd, 10), "Failed to master cmd begin");
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

    Assert::IsTrue(Types::ETaskId::I2cTask, GetI2c().MasterStart(cmd), "Failed master start 2");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress), 
        "Failed to write device address 2");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteRegisterAddress(cmd, registerAddress), 
        "Failed to write register address 2");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterWriteByte(cmd, value), 
        "Failed to write value");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterStop(cmd), 
        "Failed master stop");

    Assert::IsTrue(
        Types::ETaskId::I2cTask, 
        GetI2c().MasterCmdBegin(_port, cmd, 10), 
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

    Assert::IsTrue(
        Types::ETaskId::I2cTask, GetI2c().MasterStart(cmd), 
        "Failed master start 2");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, GetI2c().MasterWriteDeviceAddress(cmd, deviceAddress),
        "Failed to write device address 2");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, GetI2c().MasterWriteRegisterAddress(cmd, registerAddress), 
        "Failed to write register address 2");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, GetI2c().MasterWrite(cmd, data, length), 
        "Failed to write");
    Assert::IsTrue(
        Types::ETaskId::I2cTask, GetI2c().MasterStop(cmd),
        "Failed master stop");

    Assert::IsTrue(Types::ETaskId::I2cTask, GetI2c().MasterCmdBegin(_port, cmd, 50), "Failed to master cmd begin");
    GetI2c().CmdLinkDelete(cmd);
}
