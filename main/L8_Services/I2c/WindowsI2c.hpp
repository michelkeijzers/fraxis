#pragma once

#include "I2c.hpp"

class WindowsI2c : public I2c
{
public:
    WindowsI2c();
    ~WindowsI2c();

private:
    bool IsValidPort(uint8_t port) override;
    bool ParamConfig(uint8_t port, uint8_t sdaPin, uint8_t sclPin, uint32_t frequency) override;
    bool DriverInstall(uint8_t port) override;
    bool MasterWriteToDevice(
        uint8_t port, uint8_t deviceAddress, const uint8_t* data, size_t length, uint32_t timeoutInMs) override;
    bool MasterReadFromDevice(
        uint8_t port, uint8_t deviceAddress, uint8_t* data, size_t length, uint32_t timeoutInMs) override;

    void* CmdLinkCreate() override;
    void CmdLinkDelete(void* cmd) override;

    bool MasterStart(void* cmd) override;
    bool MasterStop(void* cmd) override;
    bool MasterWriteDeviceAddress(void* cmd, uint8_t deviceAddress) override;
    bool MasterWriteRegisterAddress(void* cmd, uint8_t registerAddress) override;
    bool MasterWriteByte(void* cmd, uint8_t byteToWrite) override;
    bool MasterReadByte(void* cmd, uint8_t* byteToRead) override;
    bool MasterWrite(void* cmd, const uint8_t* data, size_t length) override;
    bool MasterRead(void* cmd, uint8_t* data, size_t length) override;
    bool MasterCmdBegin(uint8_t port, void* cmd, uint32_t timeoutInMs) override;
};
