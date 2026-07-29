#include "LedStripsCurrentLimiter.hpp"
#include "Ws28xxDeviceModel.hpp"

LedStripsCurrentLimiter::LedStripsCurrentLimiter(uint16_t maxCurrentMa)
: _maxCurrentMa(maxCurrentMa)
{
}

void LedStripsCurrentLimiter::AddWs28xxDeviceModel(Ws28xxDeviceModel* ws28xxDeviceModel)
{
    if (ws28xxDeviceModel != nullptr)
    {
        _ws28xxDeviceModels.push_back(ws28xxDeviceModel);
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

    for (auto* ws28xxDeviceModel : _ws28xxDeviceModels)
    {
        if (ws28xxDeviceModel != nullptr)
        {
            totalCurrent += ws28xxDeviceModel->ComputeDriverBufferCurrent();
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

    for (auto* ws28xxDeviceModel : _ws28xxDeviceModels)
    {
        if (ws28xxDeviceModel != nullptr)
        {
            ws28xxDeviceModel->ScaleDriverBuffer(scale);
        }
    }
}
