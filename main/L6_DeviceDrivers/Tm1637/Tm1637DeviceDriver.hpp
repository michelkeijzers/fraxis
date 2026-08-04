#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

class Gpio;

class Tm1637DeviceDriver : public DeviceDriver
{
public:
    Tm1637DeviceDriver();
    virtual ~Tm1637DeviceDriver() = default;

    void SetGpio(Gpio& gpio);
    void SetPinsConfiguration(uint8_t clockPin, uint8_t dataPin);
    void Initialize();

    void SendToDisplay();

private:
    Gpio& GetGpio();

    void Start();
    void WriteByte(uint8_t byte);
    void Stop();

    uint8_t _clockPin;
    uint8_t _dataPin;

    Gpio* _gpio;
};
