#include "GrbBufferFiller.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

/// @brief Lookup table for gamma correction
/// @details These values are generated from website https://tool-box.net/en/emb/led-gamma-lut-generator
/// Settings: 
/// - PWM Minimum: 1: To make sure that not the first series of values are all 0, meaning invisible. So a value of 1 
///   ensures the pixel will be visible. 
///   However, because of this and to prevent a value with 0 will be dark, the first index has been manually set to 0.
/// - PWM Maximum: 255: Max value to apply to WS2812.
/// - Dimming Steps: 255: To be able to convert all values from 0 to 255
/// - Gamma Value: 2.2: Default gamma correction.
uint8_t GAMMA_LOOKUP_TABLE[256] = 
{
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5,
    5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 12, 12, 12, 13, 13, 14, 14, 14, 15, 15, 16, 16, 
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25, 25, 26, 27, 27, 28, 29, 29, 30, 31, 31, 32, 33, 33, 
    34, 35, 36, 36, 37, 38, 39, 39, 40, 41, 42, 43, 43, 44, 45, 46, 47, 48, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 
    59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 77, 78, 79, 80, 81, 82, 84, 85, 86, 87, 88, 90, 
    91, 92, 93, 95, 96, 97, 98, 100, 101, 102, 104, 105, 106, 108, 109, 111, 112, 113, 115, 116, 118, 119, 120, 122, 
    123, 125, 126, 128, 129, 131, 132, 134, 135, 137, 139, 140, 142, 143, 145, 147, 148, 150, 151, 153, 155, 156, 158, 
    160, 162, 163, 165, 167, 168, 170, 172, 174, 176, 177, 179, 181, 183, 185, 186, 188, 190, 192, 194, 196, 198, 200, 
    201, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 232, 234, 236, 238, 240, 242, 244, 246, 
    248, 251, 253, 255
};

GrbBufferFiller::GrbBufferFiller(
    Ws28xxDeviceModel::RgbStruct* sourceBuffer, uint16_t nrOfLeds, Ws28xxDeviceModel::RgbStruct* destinationBuffer)
:   _sourceBuffer(sourceBuffer), _nrOfLeds(nrOfLeds), _destinationBuffer(destinationBuffer)
{
}

GrbBufferFiller::~GrbBufferFiller()
{
}

/// @brief  Applies gamma correction and current limiting and brightness control.
/// @todo For the loops, use uint_fast16_t (but only for ESP32).
void GrbBufferFiller::Run()
{
    uint32_t totalBrightness = 0;
    for (uint16_t index = 0; index < _nrOfLeds; ++index)
    {
        auto sourceBuffer = _sourceBuffer[index];
        uint8_t green = GAMMA_LOOKUP_TABLE[sourceBuffer.green];
        uint8_t red   = GAMMA_LOOKUP_TABLE[sourceBuffer.red];
        uint8_t blue  = GAMMA_LOOKUP_TABLE[sourceBuffer.blue];
        totalBrightness += green + red + blue;
        _destinationBuffer[index].green = green;
        _destinationBuffer[index].red   = red;
        _destinationBuffer[index].blue  = blue;
    }

    uint8_t brightnessFactor = ComputeBrightnessFactor(totalBrightness);
    for (uint16_t index = 0; index < _nrOfLeds; ++index)
    {
        _destinationBuffer[index].green = (_destinationBuffer[index].green * brightnessFactor) >> 8;
        _destinationBuffer[index].red   = (_destinationBuffer[index].red   * brightnessFactor) >> 8;
        _destinationBuffer[index].blue  = (_destinationBuffer[index].blue  * brightnessFactor) >> 8;
    }
}

uint8_t GrbBufferFiller::ComputeBrightnessFactor(uint32_t totalBrightness)
{
    const uint32_t maxLedStripsCurrent = 5000; // in mA
    const uint32_t allowedBrightness = (maxLedStripsCurrent * HUNDRED_BRIGHTNESS_UNIT_PER_MA) / 100;
    return (totalBrightness <= allowedBrightness) ? 255 : ((allowedBrightness * 255) / totalBrightness);
}
