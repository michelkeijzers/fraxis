#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

class Tm1637DeviceDriver : public DeviceDriver
{
public:
    Tm1637DeviceDriver();
    ~Tm1637DeviceDriver();

    virtual void SetPinsConfiguration(uint8_t clockPin, uint8_t dataPin) = 0;

    virtual void SendToDisplay() = 0;
};
