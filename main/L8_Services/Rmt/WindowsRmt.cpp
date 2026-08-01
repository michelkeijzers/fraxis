#include "WindowsRmt.hpp"

WindowsRmt::WindowsRmt()
{}

WindowsRmt::~WindowsRmt()
{}

bool WindowsRmt::DelEncoder()
{
    return true;
}

bool WindowsRmt::DelChannel()
{
    return true;
}

bool WindowsRmt::NewTxChannel(uint8_t pin)
{
    return true;
}

bool WindowsRmt::Enable()
{
    return true;
}

bool WindowsRmt::NewSimpleEncoder()
{
    return true;
}

bool WindowsRmt::Transmit(const void* payload, size_t payload_bytes)
{
    return true;
}

bool WindowsRmt::TxWaitAllDone()
{
    return true;
}
