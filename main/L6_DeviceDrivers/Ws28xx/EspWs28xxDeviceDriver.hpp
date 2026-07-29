#pragma once

#include "Ws28xxDeviceDriver.hpp"

class EspWs28xxDeviceDriver : public Ws28xxDeviceDriver
{
public:
    EspWs28xxDeviceDriver();
    ~EspWs28xxDeviceDriver();

    void WriteToLedStrip() override;
};
