#pragma once

#include "../DomainModel.hpp"
#include "../../L3_Messages/Types.hpp"
#include "../../L3_Messages/Color.hpp"
#include "../../L3_Messages/Position.hpp"
#include "../../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"

class Ws28xxDeviceModel;

class LedStrips : public IDomainModel
{
public:
    static const uint8_t NUMBER_OF_LED_STRIPS = 5;
    static const uint8_t NUMBER_OF_LEDS_PER_LED_STRIP = 72;
    static const uint16_t NUMBER_OF_LEDS = NUMBER_OF_LED_STRIPS * NUMBER_OF_LEDS_PER_LED_STRIP;

    LedStrips();
    ~LedStrips();

    Ws28xxDeviceModel& GetWs28xxDeviceModel();
    void SetDeviceModel(IDeviceModel& deviceModel) override;

    void SetPixel(Position& position, Color& color);

private:
    Color _leds[NUMBER_OF_LEDS_PER_LED_STRIP][NUMBER_OF_LED_STRIPS];
    Types::ELedStripsOrientation _orientation;

    Ws28xxDeviceModel* _ws28xxDeviceModel; 

    void SwapXyIfVertical(Position& position);
    uint16_t GetDeviceModelLedIndex(Position& position) const;
};
