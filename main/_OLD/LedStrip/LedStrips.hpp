#pragma once

#include <cstdint>
#include "IComponent.hpp"
#include "../../Common/Components/LedStrip/Ws28xxDeviceModel.hpp"

class LedStrips
{
public:
    static constexpr uint8_t  NUMBER_OF_LED_STRIPS          = 5;
    static constexpr uint16_t NUMBER_OF_LEDS_PER_LED_STRIP  = 72;
    static constexpr uint16_t NUMBER_OF_LEDS                = NUMBER_OF_LED_STRIPS * NUMBER_OF_LEDS_PER_LED_STRIP;

    enum EOrientation
    {
        Horizontal, // 5 rows × 72 columns
        Vertical    // 72 rows × 5 columns
    };

    LedStrips(Ws28xxDeviceModel& ws28xxDeviceModel);
    virtual ~LedStrips() = default;

    const Ws28xxDeviceModel::Pixel GetPixel(uint8_t x, uint8_t y) const;
    void SetPixel(uint8_t x, uint8_t y,
                  uint8_t red, uint8_t green, uint8_t blue);

    void Fill(uint8_t red, uint8_t green, uint8_t blue);

    // Combined buffer view (strip 0, then 1, ..., 4)
    const Ws28xxDeviceModel::Pixel* GetActiveBuffer() const;

    void SetOrientation(EOrientation orientation) { _orientation = orientation;}

private:
    uint16_t GetLedIndex(uint8_t x, uint8_t y) const; 

private:
    EOrientation  _orientation;

    Ws28xxDeviceModel& _ws28xxDeviceModel;
};
