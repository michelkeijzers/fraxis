#include "LedStrips.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L9_Utilities/Algorithm/Algorithm.hpp"

LedStrips::LedStrips()
{
}

LedStrips::~LedStrips()
{
}

Ws28xxDeviceModel& LedStrips::GetWs28xxDeviceModel()
{
    return *_ws28xxDeviceModel;
}

void LedStrips::SetDeviceModel(IDeviceModel& deviceModel)
{
    _ws28xxDeviceModel = static_cast<Ws28xxDeviceModel*>(&deviceModel);
}

void LedStrips::SetPixel(Position& position, Color& color)
{
    uint8_t x = position.GetX();
    uint8_t y = position.GetY();
    if (_orientation == Types::ELedStripsOrientation::Horizontal)
    {
        Algorithm::swap(x, y);
    }
    _leds[x][y] = color;
    //TODO GetWs28xxDeviceModel().SetPixel(0, color.GetRed(), color.GetGreen(), color.GetBlue());
}

uint16_t LedStrips::GetLedIndex(Position position) const
{
    return position.GetX() * NR_OF_LEDS_X + position.GetY(); //TODO FIX

/*
TODO
uint16_t LedStrips::GetLedIndex(uint8_t x, uint8_t y) const
{
    if (_orientation == Horizontal)
    {
        // 5 rows × 72 columns
        // y=0 is top, but physical chain starts at bottom
        uint8_t physicalRow = (NUMBER_OF_LED_STRIPS - 1) - y; // 4 - y

        if ((physicalRow % 2) == 0)
        {
            // even row: left → right
            return physicalRow * NUMBER_OF_LEDS_PER_LED_STRIP + x;
        }
        else
        {
            // odd row: right → left
            return physicalRow * NUMBER_OF_LEDS_PER_LED_STRIP + (NUMBER_OF_LEDS_PER_LED_STRIP - 1 - x);
        }
    }
    else // Vertical
    {
        // 72 rows × 5 columns
        // x=0 is left, but physical chain starts at right
        uint8_t physicalCol = (NUMBER_OF_LED_STRIPS - 1) - x; // 4 - x

        if ((physicalCol % 2) == 0)
        {
            // even column: top → bottom
            return physicalCol * NUMBER_OF_LEDS_PER_LED_STRIP + y;
        }
        else
        {
            // odd column: bottom → top
            return physicalCol * NUMBER_OF_LEDS_PER_LED_STRIP + (NUMBER_OF_LEDS_PER_LED_STRIP - 1 - y);
        }
    }
*/
}
