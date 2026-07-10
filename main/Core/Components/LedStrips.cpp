#include "LedStrips.hpp"

LedStrips::LedStrips(LedStripModel& ledStripModel)
: _orientation(Horizontal), _ledStripModel(ledStripModel)
{
}

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
}

void LedStrips::SetPixel(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t ledIndex = GetLedIndex(x, y);

    if (ledIndex >= NUMBER_OF_LEDS)
        return;

    _ledStripModel.SetPixel(ledIndex, red, green, blue);
}

void LedStrips::Fill(uint8_t red, uint8_t green, uint8_t blue)
{
    _ledStripModel.Fill(red, green, blue);
}

const LedStripModel::Pixel* LedStrips::GetActiveBuffer() const
{
    // Return buffer of first strip; caller can iterate over strips if needed.
    // If you want a single contiguous 5×72 buffer, you’d build that elsewhere.
    return _ledStripModel.GetActiveBuffer();
}
