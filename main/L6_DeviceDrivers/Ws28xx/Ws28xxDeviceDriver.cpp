#include "Ws28xxDeviceDriver.hpp"
#include "Ws2812Rmt.hpp"
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

void Ws28xxDeviceDriver::SetRmt(Rmt& rmt)
{
    _rmt = &rmt;
}

uint16_t Ws28xxDeviceDriver::GetNrOfLeds() const
{
    return _nrOfLeds;
}

void Ws28xxDeviceDriver::Initialize()
{
    _nrOfLeds = GetWs28xxDeviceModel().GetNrOfLeds();
    _ws2812rmt = new Ws2812Rmt(_dataPin, GetNrOfLeds(), *_rmt);
    _ws2812rmt->Initialize();
}

Ws28xxDeviceModel& Ws28xxDeviceDriver::GetWs28xxDeviceModel() 
{
    return static_cast<Ws28xxDeviceModel&>(GetDeviceModel()); 
}

void Ws28xxDeviceDriver::WriteToLedStrip()
{
    Ws28xxDeviceModel::RgbStruct destinationBuffer[GetNrOfLeds()];
    GetWs28xxDeviceModel().FillGrbBufferToSend(destinationBuffer);
    _ws2812rmt->Send(reinterpret_cast<const unsigned char*>(destinationBuffer));
}
