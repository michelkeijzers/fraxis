#ifdef ESP_PLATFORM

#pragma once

#include "Tm1637DeviceDriver.hpp"
#include <cstdint>

class EspTm1637DeviceDriver : public Tm1637DeviceDriver
{
public:
    EspTm1637DeviceDriver();
    ~EspTm1637DeviceDriver();

    void SetPinsConfiguration(uint8_t clockPin, uint8_t dataPin) override;
    void Initialize() override;

    void SendToDisplay() override;

private:
    gpio_num_t _clockPin;
    gpio_num_t _dataPin;    
};

#endif // ESP_PLATFORM
