#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

class Ws28xxDeviceModel;

class Ws28xxDeviceDriver : public DeviceDriver
{
public:
    Ws28xxDeviceDriver();
    ~Ws28xxDeviceDriver();

    virtual void SetDataPin(uint8_t dataPin);
    virtual void Initialize() = 0;

    uint8_t GetDataPin() const;

    virtual void WriteToLedStrip() = 0;

protected:
    Ws28xxDeviceModel& GetWs28xxDeviceModel();
    uint16_t GetNrOfLeds() const;

private:
    uint8_t _dataPin;
    uint16_t _nrOfLeds;
};
