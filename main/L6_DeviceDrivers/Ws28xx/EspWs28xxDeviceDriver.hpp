#pragma once

#include "Ws28xxDeviceDriver.hpp"

class Ws2812Rmt;

class EspWs28xxDeviceDriver : public Ws28xxDeviceDriver
{
public:
    EspWs28xxDeviceDriver();
    ~EspWs28xxDeviceDriver();

    void SetDataPin(uint8_t dataPin) override;
    void Initialize() override;

    void WriteToLedStrip() override;

private:
    Ws2812Rmt* _ws2812;
    uint8_t _gpioPin;
};
