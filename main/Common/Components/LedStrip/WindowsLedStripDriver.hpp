#pragma once
#include <vector>
#include <cstdint>
#include "LedStripDriver.hpp"
#include "LedStripModel.hpp"

class GdiLedStrips;

class WindowsLedStripDriver : public LedStripDriver
{
public:
    WindowsLedStripDriver();
    virtual ~WindowsLedStripDriver() = default;

    void Initialize() override {};

    // Send one physical LED strip buffer
    void Send(const LedStripModel::Pixel* buffer, uint16_t count) override;

    std::vector<LedStripModel::Pixel> GetBuffer() { return _bufferLastSent;};

private:
    uint16_t   _numberOfLeds;

    std::vector<LedStripModel::Pixel> _bufferLastSent;
};
