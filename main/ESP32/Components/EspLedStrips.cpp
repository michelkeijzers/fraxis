#include "EspLedStrips.hpp"
#include "Ws2812Rmt.hpp"

static Ws2812Rmt ws(GPIO_NUM_18, EspLedStrips::NumberOfLeds);

EspLedStrips::EspLedStrips() : LedStrips()
{
}

void EspLedStrips::Initialize()
{
    ws.Initialize();
}
	
void EspLedStrips::Update()
{
    static uint8_t grb[NumberOfLeds * 3];

    for (uint16_t i = 0; i < NumberOfLeds; ++i)
    {
        grb[i*3 + 0] = GetPixel(i).green;
        grb[i*3 + 1] = GetPixel(i).red;
        grb[i*3 + 2] = GetPixel(i).blue;
    }

    ws.Send(grb);
}
