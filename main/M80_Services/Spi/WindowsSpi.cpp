#include "WindowsSpi.hpp"

bool WindowsSpi::IsValidPort(
    uint8_t port)
{
    return (port == 0) || (port == 1);
}

bool WindowsSpi::ParamConfig(
    uint8_t /* port */,
    uint8_t /* mosiPin */,
    uint8_t /* misoPin */,
    uint8_t /* sclkPin */,
    uint32_t /* frequency */)
{
    // NOSONAR TODO SPI
    return true;
}

bool WindowsSpi::DriverInstall(
    uint8_t /* port */)
{
    // NOSONAR TODO SPI
    return true;
}

bool WindowsSpi::Transfer(
    uint8_t /* port */,
    const uint8_t* dataOut,
    uint8_t* dataIn,
    size_t length,
    uint32_t /* timeoutInMs */)
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

// NOSONAR TODO SPI
bool WindowsSpi::Write(
    uint8_t /* port */,
    const uint8_t* /* data */,
    size_t /* length */,
    uint32_t /* timeoutInMs */)
{
    return true;
}

// NOSONAR TODO SPI
bool WindowsSpi::Read( // NOSONAR: TODO SPI replace to std::span
    uint8_t /* port */,
    uint8_t* data , 
    size_t length,
    uint32_t /* timeoutInMs */)
{
    for (size_t i = 0; i < length; i++)
    {
        data[i] = 0;
    }
    return true;
}

void* WindowsSpi::TransactionCreate( // NOSONAR: S5008: void * NOSONAR TODO Change type
    uint8_t /* port */,
    size_t /* length */)
{
    // NOSONAR TODO SPI
    return nullptr;
}

void WindowsSpi::TransactionDelete(
    void* /* transaction */) // NOSONAR: S5008: void * NOSONAR TODO Change type
{
    // NOSONAR TODO SPI
}

bool WindowsSpi::TransactionAddCommand(
    void* /* transaction */, // NOSONAR: S5008: void * NOSONAR TODO Change type
    uint16_t /* command */,
    size_t /* bits */)
{
    // NOSONAR TODO SPI
    return true;
}

bool WindowsSpi::TransactionAddData(
    void* /* transaction */, // NOSONAR: S5008: void * NOSONAR TODO Change type
    const uint8_t* /* data */,
    size_t /* length */,
    bool /* isRead */)
{
    return true;
}

bool WindowsSpi::TransactionExecute(
    void* /* transaction */, // NOSONAR: S5008: void * NOSONAR TODO: Change type
    uint32_t /* timeoutInMs */)
{
    return true;
}
