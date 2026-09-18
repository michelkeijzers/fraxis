
#pragma once

#include <cstdint>
#include <stddef.h>

class I2c
{
public:
    I2c() = default;
    virtual ~I2c() = default;

    virtual bool IsValidPort(
        uint8_t port) = 0;
    virtual bool ParamConfig(
        uint8_t port,
        uint8_t sdaPin, 
        uint8_t sclPin,
        uint32_t frequency) = 0;
    virtual bool DriverInstall(
        uint8_t port) = 0;

    virtual bool MasterWriteToDevice(
        uint8_t port,
        uint8_t deviceAddress,
        const uint8_t *data,
        size_t length, 
        uint32_t timeoutInMs) = 0;
    virtual bool MasterReadFromDevice(
        uint8_t port, uint8_t deviceAddress,
        uint8_t *data, 
        size_t length,
        uint32_t timeoutInMs) = 0;
    
    virtual void* CmdLinkCreate() = 0; // NOSONAR: ESP expects void*
    virtual void CmdLinkDelete(
        void* cmd) = 0; // NOSONAR: ESP expects void*

    virtual bool MasterStart(
        void* cmd) = 0; // NOSONAR: ESP expects void*
    virtual bool MasterWriteDeviceAddress(
        void* cmd, // NOSONAR: ESP expects void*
        uint8_t deviceAddress) = 0;
    virtual bool MasterWriteRegisterAddress(
        void* cmd,  // NOSONAR: ESP expects void*
        uint8_t registerAddress) = 0;
    virtual bool MasterWriteByte(
        void* cmd, // NOSONAR: ESP expects void*
        uint8_t byteToWrite) = 0;
    virtual bool MasterReadByte(
        void* cmd, // NOSONAR: ESP expects void*
        uint8_t* byteToRead) = 0;
    virtual bool MasterWrite(
        void* cmd, // NOSONAR: ESP expects void*
        const uint8_t *data,
        size_t length) = 0;
    virtual bool MasterRead(
        void* cmd, // NOSONAR: ESP expects void*
        uint8_t *data, 
        size_t length) = 0;
    virtual bool MasterStop(
        void* cmd) = 0; // NOSONAR: ESP expects void*
    virtual bool MasterCmdBegin(
        uint8_t port, 
        void* cmd,  // NOSONAR: ESP expects void*
        uint32_t timeoutInMs) = 0;
};
