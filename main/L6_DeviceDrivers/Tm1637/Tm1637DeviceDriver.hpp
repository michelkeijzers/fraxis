#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

class Gpio;

class Tm1637DeviceDriver : public DeviceDriver
{
public:
    Tm1637DeviceDriver();
    virtual ~Tm1637DeviceDriver();

    void SetGpio(Gpio& gpio);
    void SetPinsConfiguration(uint8_t clockPin, uint8_t dataPin);
    void Initialize();

    void SendToDisplay();

private:
    Gpio& GetGpio();

    virtual void Start();
    virtual void WriteByte(uint8_t byte);
    virtual void Stop();

    uint8_t _clockPin;
    uint8_t _dataPin;

    Gpio* _gpio;
};
