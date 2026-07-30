#pragma once

#include "../DeviceModel.hpp"
#include "../../L9_Utilities/Dirty/IDirty.hpp"
#include <cstdint>
#include <memory>

class Ws28xxDeviceModel : public DeviceModel, public IDirty
{
public:
    struct rgb
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    Ws28xxDeviceModel();
    ~Ws28xxDeviceModel();

    void SetNrOfLeds(uint16_t nrOfLeds);
    void Initialize() override;

    void SetPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);

private:
    std::unique_ptr<rgb[]>  _leds;
    uint16_t _nrOfLeds;

    rgb CreateRgb(uint8_t red, uint8_t green, uint8_t blue) const;
};
