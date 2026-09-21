#pragma once

#include "Spi.hpp"

class WindowsSpi : public Spi
{
public:
    WindowsSpi();
    ~WindowsSpi() = default;

private:
    bool IsValidPort(
        uint8_t port) override;
    bool ParamConfig(
        uint8_t port,
        uint8_t mosiPin,
        uint8_t misoPin,
        uint8_t sclkPin,
        uint8_t csPin,
        uint32_t frequency) override;
    bool DriverInstall(uint8_t port) override;

    bool Transfer(
        uint8_t port,
        const uint8_t* dataOut,
        uint8_t* dataIn,
        size_t length,
        uint32_t timeoutInMs) override;

    bool Write(
        uint8_t port,
        const uint8_t* data,
        size_t length,
        uint32_t timeoutInMs) override;
    bool Read(
        uint8_t port,
        uint8_t* data,
        size_t length,
        uint32_t timeoutInMs) override;

    void* TransactionCreate(
        uint8_t port,
        size_t length) override;
    void TransactionDelete(
        void* transaction) override;

    bool TransactionAddCommand(
        void* transaction,
        uint16_t command,
        size_t bits) override;
    bool TransactionAddData(
        void* transaction,
        const uint8_t* data,
        size_t length,
        bool isRead) override;
    bool TransactionExecute(
        void* transaction,
        uint32_t timeoutInMs) override;
};
