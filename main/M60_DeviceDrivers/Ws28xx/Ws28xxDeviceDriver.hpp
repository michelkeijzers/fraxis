#pragma once

#include "../DeviceDriver.hpp"
#include "Ws2812Rmt.hpp"
#include <cstdint>
#include <memory>

class Rmt;
class Ws28xxDeviceModel;

class Ws28xxDeviceDriver : public DeviceDriver
{
public:
    Ws28xxDeviceDriver();
    ~Ws28xxDeviceDriver() = default;

    void SetRmt(
        Rmt& rmt);
    void SetDataPin(
        uint8_t dataPin);
    void Initialize() override;

    uint8_t GetDataPin() const;

    void WriteToLedStrip();

private:
    Ws28xxDeviceModel& GetWs28xxDeviceModel();

    uint8_t _dataPin;
    uint16_t _nrOfLeds;

    std::unique_ptr<Ws2812Rmt> _ws2812rmt;
    Rmt* _rmt;
};
