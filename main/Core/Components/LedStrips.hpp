#pragma once

#include <cstdint>
#include "IComponent.hpp"
#include "../../Common/Components/LedStrip/LedStripModel.hpp"

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

    LedStrips(LedStripModel& ledStripModel);
    virtual ~LedStrips() = default;

    void SetPixel(uint8_t x, uint8_t y,
                  uint8_t red, uint8_t green, uint8_t blue);

    void Fill(uint8_t red, uint8_t green, uint8_t blue);

    // Combined buffer view (strip 0, then 1, ..., 4)
    const LedStripModel::Pixel* GetBuffer() const;

    // Access individual strip model
    LedStripModel&       GetStrip(uint8_t stripIndex);
    const LedStripModel& GetStrip(uint8_t stripIndex) const;

    void SetOrientation(EOrientation orientation);

private:
    uint16_t GetLedIndex(uint8_t x, uint8_t y) const; 

private:
    EOrientation  _orientation;

    LedStripModel& _ledStripModel;
};
