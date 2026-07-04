#pragma once

#include <cstdint>

class ITimer
{
public:
    virtual ~ITimer() = default;

    virtual uint32_t GetTimeInMs() = 0;
};
