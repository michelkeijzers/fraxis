#include "EspWs28xxDeviceDriver.hpp"
#include "Ws2812Rmt.hpp"
#include "../../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"

EspWs28xxDeviceDriver::EspWs28xxDeviceDriver()
: Ws28xxDeviceDriver(), _ws2812(nullptr), _gpioPin(0)
{
}

EspWs28xxDeviceDriver::~EspWs28xxDeviceDriver()
{
}

void EspWs28xxDeviceDriver::SetDataPin(uint8_t dataPin)
{
    _gpioPin = dataPin;
}

void EspWs28xxDeviceDriver::Initialize()
{
    Ws28xxDeviceDriver::Initialize();

    // Create RMT driver with correct LED count
    _ws2812 = new Ws2812Rmt(static_cast<gpio_num_t>(_gpioPin), GetNrOfLeds());
    _ws2812->Initialize();
}

void EspWs28xxDeviceDriver::WriteToLedStrip()
{
    Ws28xxDeviceModel::RgbStruct destinationBuffer[GetNrOfLeds()];
    GetWs28xxDeviceModel().FillGrbBufferToSend(destinationBuffer);
    _ws2812->Send(reinterpret_cast<const unsigned char*>(destinationBuffer));
}
