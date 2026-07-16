#if !defined(_WIN32) && !defined(_WIN64)

#pragma once

#include <cstdint>
#include "LedStripDriver.hpp"
#include "LedStripModel.hpp"
#include "driver/gpio.h"

class Ws2812Rmt; // forward declaration

class EspLedStripDriver : public LedStripDriver
{
public:
    EspLedStripDriver(uint16_t numberOfLeds, gpio_num_t gpioPin);
    virtual ~EspLedStripDriver() = default;

    void Initialize() override;

    // Send one physical LED strip buffer
    void Send(const LedStripModel::Pixel* buffer, uint16_t count) override;

private:
    uint16_t   _numberOfLeds;
    gpio_num_t _gpioPin;

    Ws2812Rmt* _ws2812;   // allocated in Initialize()
};

#endif
