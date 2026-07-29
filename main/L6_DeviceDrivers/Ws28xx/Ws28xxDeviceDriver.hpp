#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

class Ws28xxDeviceDriver : public DeviceDriver
{
public:
    Ws28xxDeviceDriver();
    ~Ws28xxDeviceDriver();

    void SetDataPin(uint8_t dataPin);
    void Initialize() override;

    uint8_t GetDataPin() const;

    virtual void WriteToLedStrip() = 0;

private:
    uint8_t _dataPin;
};
