
#pragma once

#include <cstdint>
#include <stddef.h>

class Spi
{
public:
    Spi() = default;
    virtual ~Spi() = default;

    virtual bool IsValidPort(
        uint8_t port) = 0;
    virtual bool ParamConfig(
        uint8_t port,
        uint8_t mosiPin,
        uint8_t misoPin,
        uint8_t sclkPin,
        uint8_t csPin,
        uint32_t frequency) = 0;
    virtual bool DriverInstall(
        uint8_t port) = 0;

    virtual bool Transfer(
        uint8_t port,
        const uint8_t* dataOut,
        uint8_t* dataIn,
        size_t length,
        uint32_t timeoutInMs) = 0;

    virtual bool Write(
        uint8_t port,
        const uint8_t* data,
        size_t length,
        uint32_t timeoutInMs) = 0;
    virtual bool Read(
        uint8_t port,
        uint8_t* data,
        size_t length,
        uint32_t timeoutInMs) = 0;

    virtual void* TransactionCreate(
        uint8_t port,
        size_t length) = 0;
    virtual void TransactionDelete(
        void* transaction) = 0;

    virtual bool TransactionAddCommand(
        void* transaction,
        uint16_t command,
        size_t bits) = 0;
    virtual bool TransactionAddData(
        void* transaction,
        const uint8_t* data,
        size_t length,
        bool isRead) = 0;
    virtual bool TransactionExecute(
        void* transaction,
        uint32_t timeoutInMs) = 0;
};
