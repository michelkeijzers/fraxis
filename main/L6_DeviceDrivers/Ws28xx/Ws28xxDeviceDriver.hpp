#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>

class Rmt;
class Ws2812Rmt;
class Ws28xxDeviceModel;

class Ws28xxDeviceDriver : public DeviceDriver
{
public:
    Ws28xxDeviceDriver();
    ~Ws28xxDeviceDriver();

    void SetRmt(Rmt& rmt);
    void SetDataPin(uint8_t dataPin);
    void Initialize() override;

    uint8_t GetDataPin() const;

    void WriteToLedStrip();

protected:
    Ws28xxDeviceModel& GetWs28xxDeviceModel();
    uint16_t GetNrOfLeds() const;

private:
    uint8_t _dataPin;
    uint16_t _nrOfLeds;

    Ws2812Rmt* _ws2812rmt;
    Rmt* _rmt;
};
