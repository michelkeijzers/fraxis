#pragma once

#include <cstdint>
#include "../../Core/Services/ITimer.hpp"

class EspTimer : public ITimer
{
public:
    EspTimer();

    uint32_t GetTimeInMs();
};
