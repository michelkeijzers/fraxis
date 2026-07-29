#include "Ws28xxDeviceDriver.hpp"

Ws28xxDeviceDriver::Ws28xxDeviceDriver()
{
}

Ws28xxDeviceDriver::~Ws28xxDeviceDriver()
{
}

uint8_t Ws28xxDeviceDriver::GetDataPin() const
{
    return _dataPin;
}

void Ws28xxDeviceDriver::SetDataPin(uint8_t dataPin)
{
    _dataPin = dataPin;
}

void Ws28xxDeviceDriver::Initialize()
{
    //TODO
}
