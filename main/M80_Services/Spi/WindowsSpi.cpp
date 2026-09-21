#include "WindowsSpi.hpp"

WindowsSpi::WindowsSpi()
{
}

bool WindowsSpi::IsValidPort(
    uint8_t port)
{
    return (port == 0) || (port == 1);
}

bool WindowsSpi::ParamConfig(
    uint8_t port,
    uint8_t mosiPin,
    uint8_t misoPin,
    uint8_t sclkPin,
    uint8_t csPin,
    uint32_t frequency)
{
    return true;
}

bool WindowsSpi::DriverInstall(
    uint8_t port)
{
    return true;
}

bool WindowsSpi::Transfer(
    uint8_t port,
    const uint8_t* dataOut,
    uint8_t* dataIn,
    size_t length,
    uint32_t timeoutInMs)
{
    if (dataIn != nullptr)
    {
        for (size_t i = 0; i < length; i++)
        {
            dataIn[i] = dataOut != nullptr ? dataOut[i] : 0;
        }
    }
    return true;
}

bool WindowsSpi::Write(
    uint8_t port,
    const uint8_t* data,
    size_t length,
    uint32_t timeoutInMs)
{
    return true;
}

bool WindowsSpi::Read(
    uint8_t port,
    uint8_t* data,
    size_t length,
    uint32_t timeoutInMs)
{
    for (size_t i = 0; i < length; i++)
    {
        data[i] = 0;
    }
    return true;
}

void* WindowsSpi::TransactionCreate(
    uint8_t port,
    size_t length)
{
    return nullptr;
}

void WindowsSpi::TransactionDelete(
    void* transaction)
{
}

bool WindowsSpi::TransactionAddCommand(
    void* transaction,
    uint16_t command,
    size_t bits)
{
    return true;
}

bool WindowsSpi::TransactionAddData(
    void* transaction,
    const uint8_t* data,
    size_t length,
    bool isRead)
{
    return true;
}

bool WindowsSpi::TransactionExecute(
    void* transaction,
    uint32_t timeoutInMs)
{
    return true;
}
