#include "WindowsI2c.hpp"
#include "../../L7_WindowsGdi/GdiSimulator.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include "windows.h"

WindowsI2c::WindowsI2c()
{}

WindowsI2c::~WindowsI2c()
{}

bool WindowsI2c::IsValidPort(uint8_t port)
{
    return (port == 0) || (port == 1);
}

bool WindowsI2c::ParamConfig(uint8_t port, uint8_t sdaPin, uint8_t sclPin, uint32_t frequency)
{
    return true;
}

bool WindowsI2c::DriverInstall(uint8_t port)
{
    return true;
}

bool WindowsI2c::MasterWriteToDevice(
    uint8_t port, uint8_t deviceAddress, const uint8_t* data, size_t length, uint32_t timeoutInMs)
{
    PostMessage(simulatorContext.hWndMain, WM_I2C_MASTER_WRITE_TO_DEVICE, deviceAddress, 0);
    return true;
}

bool WindowsI2c::MasterReadFromDevice(
    uint8_t port, uint8_t deviceAddress, uint8_t* data, size_t length, uint32_t timeoutInMs)
{
    return true;
}

void* WindowsI2c::CmdLinkCreate()
{
    return (void*) 0x12345678;
}

void WindowsI2c::CmdLinkDelete(void* cmd)
{
}

bool WindowsI2c::MasterStart(void* cmd)
{
    return true;
}

bool WindowsI2c::MasterWriteDeviceAddress(void* cmd, uint8_t deviceAddress)
{
    return true;
}

bool WindowsI2c::MasterWriteRegisterAddress(void* cmd, uint8_t registerAddress)
{
    return true;
}

bool WindowsI2c::MasterWriteByte(void* cmd, uint8_t byteToWrite)
{
    return true;
}

bool WindowsI2c::MasterReadByte(void* cmd, uint8_t* byteToRead)
{
    return true;
}

bool WindowsI2c::MasterWrite(void* cmd, const uint8_t* data, size_t length)
{
    return true;
}

bool WindowsI2c::MasterRead(void* cmd, uint8_t* data, size_t length)
{
    return true;
}

bool WindowsI2c::MasterStop(void* cmd)
{
    return true;
}

bool WindowsI2c::MasterCmdBegin(uint8_t port, void* cmd, uint32_t timeoutInMs)
{
    return true;
}
