#include "LedStrips.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L9_Utilities/Algorithm/Algorithm.hpp"

LedStrips::LedStrips()
    : _leds{},
    _orientation(Types::ELedStripsOrientation::Horizontal),
    _ws28xxDeviceModel(nullptr)
{
    Color black(0, 0, 0);
    for (uint8_t ledStripIndex = 0; ledStripIndex < LedStrips::NUMBER_OF_LED_STRIPS; ledStripIndex++)
    {
        for (uint8_t ledIndex = 0; ledIndex < LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP; ledIndex++)
        {
            _leds[ledIndex][ledStripIndex] = black;
        }
    }
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
    SwapXyIfVertical(position);
    _leds[x][y] = color;
    uint16_t ledIndex = GetDeviceModelLedIndex(position);
    GetWs28xxDeviceModel().SetPixel(ledIndex, color.GetRed(), color.GetGreen(), color.GetBlue());
}

void LedStrips::SetFrameReady()
{
    GetWs28xxDeviceModel().SetFrameReady();
}

void LedStrips::SwapXyIfVertical(Position& position)
{
    if (_orientation == Types::ELedStripsOrientation::Vertical)
    {
        Algorithm::Swap(position.GetX(), position.GetY());
    }
}

/// @brief Calculates the led strip index for the physical (single led strip). 
/// @details For both the 5 led strips (domain model) and single led strip (device model), the left bottom coordinate is 
/// (0, 0).
/// The input position is already expected to be in horizontal layout (72x5).
/// The led strips are layout in the following way:
///
///      x :                            0   1   2   3   4   5      65  66  67  68  69  70  71   
///  y = 4 :  (start of led strip 5):  288 289 290 291 292 293 ... 353 354 355 356 357 358 359 (end of led strip   4)
///  y = 3 :  (end of led strip   3):  287 286 285 284 283 282 ... 222 221 220 219 218 217 216 (start of led strip 3)
///  y = 2 :  (start of led strip 2):  144 145 146 147 148 149 ... 209 210 211 212 213 214 215 (end of led strip   2)
///  y = 1 :  (end of led strip   1):  143 142 141 140 139 138 ...  78  77  76  75  74  73  72 (start of led strip 1)
///  y = 0 :  (start of led strip 0:     0   1   2   3   4   5 ...  65  66  67  68  69  70  71 (end of led strip   0)

/// @return 
uint16_t LedStrips::GetDeviceModelLedIndex(Position& position) const
{
    uint8_t x = position.GetX();
    uint8_t y = position.GetY();
    return y * NUMBER_OF_LEDS_PER_LED_STRIP + ((y % 2 == 0) ? x : (NUMBER_OF_LEDS_PER_LED_STRIP - 1 - x));
}
