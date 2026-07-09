#pragma once

#include <cstdint>
#include "../IDriver.hpp"
#include "LedStripModel.hpp"

class LedStripDriver : public IDriver
{
public:
    LedStripDriver() = default;
    virtual ~LedStripDriver() = default;

    // Initialize hardware (GPIO, RMT, etc.)
    virtual void Initialize() = 0;

    // Send one physical LED strip buffer
    virtual void Send(const LedStripModel::Pixel* buffer, uint16_t count) = 0;
};
