#pragma once

#include "Ws28xxDriver.hpp"

class EspWs28xxDriver : public Ws28xxDriver
{
public:
    EspWs28xxDriver();
    ~EspWs28xxDriver() = default;
};
