#include "Ws28xxDeviceDriver.hpp"
#include "../../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"

Ws28xxDeviceDriver::Ws28xxDeviceDriver()
: _dataPin(0), _nrOfLeds(0)
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

uint16_t Ws28xxDeviceDriver::GetNrOfLeds() const
{
    return _nrOfLeds;
}

void Ws28xxDeviceDriver::Initialize()
{
    _nrOfLeds = GetWs28xxDeviceModel().GetNrOfLeds();
}

Ws28xxDeviceModel& Ws28xxDeviceDriver::GetWs28xxDeviceModel() 
{
    return static_cast<Ws28xxDeviceModel&>(GetDeviceModel()); 
}
