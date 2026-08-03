#pragma once

#include "Ws28xxDeviceModel.hpp"
#include <stdint.h>

class GrbBufferFiller {
public:
    GrbBufferFiller(
        Ws28xxDeviceModel::RgbStruct* sourceBuffer, 
        uint16_t nrOfLeds,Ws28xxDeviceModel::RgbStruct* destinationBuffer,
        uint16_t maxCurrentConsumption);
    ~GrbBufferFiller();

    void Run();

private:
    Ws28xxDeviceModel::RgbStruct* _sourceBuffer;
    uint16_t _nrOfLeds;
    Ws28xxDeviceModel::RgbStruct* _destinationBuffer;
    uint16_t _maxCurrentConsumption;

    uint8_t ComputeBrightnessFactor(
        uint32_t totalBrightness);

    /// @brief  This is the brightness unit per mA. This is used to compute the brightness factor.
    /// @details Every LED has 255 + 255 + 255 (for r, g, b) = 765 brightness units. 
    /// This corresponds to white and uses 60 mA. For 1 mA the brightness is 765 / 60 = 12.75.
    /// To prevent floating points this value is multiplied by 100.
    static constexpr uint16_t HUNDRED_BRIGHTNESS_UNIT_PER_MA = 1275;
};
