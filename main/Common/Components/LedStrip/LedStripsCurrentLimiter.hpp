#pragma once

#include <cstdint>
#include <vector>

class Ws28xxDeviceModel;

class LedStripsCurrentLimiter
{
public:
    LedStripsCurrentLimiter(uint16_t maxCurrentMa);

    void AddWs28xxDeviceModel(Ws28xxDeviceModel* strip);
    void ApplyGlobalCurrentLimit();

private:
    std::vector<Ws28xxDeviceModel*> _ws28xxDeviceModels;

    uint32_t ComputeTotalCurrent() const;
    uint16_t ComputeScaleFactor(uint32_t totalCurrent);
    void ApplyScaleToAllStrips(uint16_t scale);

    uint16_t _maxCurrentMa;
};
