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
    static const uint8_t NR_OF_LEDS_X = 5;
    static const uint8_t NR_OF_LEDS_Y = 72;

    LedStrips();
    ~LedStrips();

    Ws28xxDeviceModel& GetWs28xxDeviceModel();
    void SetDeviceModel(IDeviceModel& deviceModel) override;

    void SetPixel(Position& position, Color& color);

    uint16_t GetLedIndex(Position position) const;

private:
    Color _leds[NR_OF_LEDS_X][NR_OF_LEDS_Y];
    Types::ELedStripsOrientation _orientation;

    Ws28xxDeviceModel* _ws28xxDeviceModel; 
};
