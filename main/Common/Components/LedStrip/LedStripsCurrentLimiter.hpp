#pragma once

#include <cstdint>
#include <vector>

class LedStripModel;

class LedStripsCurrentLimiter
{
public:
    LedStripsCurrentLimiter(uint16_t maxCurrentMa);

    void AddLedStripModel(LedStripModel* strip);
    void ApplyGlobalCurrentLimit();

private:
    std::vector<LedStripModel*> _ledStripModels;

    uint32_t ComputeTotalCurrent() const;
    uint16_t ComputeScaleFactor(uint32_t totalCurrent);
    void ApplyScaleToAllStrips(uint16_t scale);

    uint16_t _maxCurrentMa;
};
