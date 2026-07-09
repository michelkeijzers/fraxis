#if !defined(_WIN32) && !defined(_WIN64)

#include "EspLedStripDriver.hpp"
#include "Ws2812Rmt.hpp"

EspLedStripDriver::EspLedStripDriver(uint16_t numberOfLeds, gpio_num_t gpioPin)
    : _numberOfLeds(numberOfLeds),
      _gpioPin(gpioPin)
{
}


void EspLedStripDriver::Initialize()
{
    // Create RMT driver with correct LED count
    _ws2812 = new Ws2812Rmt(_gpioPin, _numberOfLeds);
    _ws2812->Initialize();
}

void EspLedStripDriver::Send(const LedStripModel::Pixel* buffer, uint16_t count)
{
    static uint8_t grb[1024 * 3]; // enough for 1024 LEDs, adjust if needed

    for (uint16_t i = 0; i < count; ++i)
    {
        grb[i*3 + 0] = buffer[i].green;
        grb[i*3 + 1] = buffer[i].red;
        grb[i*3 + 2] = buffer[i].blue;
    }

    _ws2812->Send(grb);
}

#endif