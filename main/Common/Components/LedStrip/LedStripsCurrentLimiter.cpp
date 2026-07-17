#include "LedStripsCurrentLimiter.hpp"
#include "LedStripModel.hpp"

LedStripsCurrentLimiter::LedStripsCurrentLimiter(uint16_t maxCurrentMa)
: _maxCurrentMa(maxCurrentMa)
{
}

void LedStripsCurrentLimiter::AddLedStripModel(LedStripModel* ledStripModel)
{
    if (ledStripModel != nullptr)
    {
        _ledStripModels.push_back(ledStripModel);
    }
}

void LedStripsCurrentLimiter::ApplyGlobalCurrentLimit()
{
    uint32_t totalCurrent = ComputeTotalCurrent();
    uint16_t scale = ComputeScaleFactor(totalCurrent);
    ApplyScaleToAllStrips(scale);
}

uint32_t LedStripsCurrentLimiter::ComputeTotalCurrent() const
{
    uint32_t totalCurrent = 0;

    for (auto* ledStripModel : _ledStripModels)
    {
        if (ledStripModel != nullptr)
        {
            totalCurrent += ledStripModel->ComputeDriverBufferCurrent();
        }
    }

    return totalCurrent;
}


uint16_t LedStripsCurrentLimiter::ComputeScaleFactor(uint32_t totalCurrent)
{
    if (totalCurrent <= _maxCurrentMa)
    {
        return 256; // 1.0 in fixed-point (8.8 format)
    }

    return static_cast<uint16_t>((_maxCurrentMa * 256) / totalCurrent);
}

void LedStripsCurrentLimiter::ApplyScaleToAllStrips(uint16_t scale)
{
    if (scale >= 256)
        return; // no limiting needed

    for (auto* ledStripModel : _ledStripModels)
    {
        if (ledStripModel != nullptr)
        {
            ledStripModel->ScaleDriverBuffer(scale);
        }
    }
}
