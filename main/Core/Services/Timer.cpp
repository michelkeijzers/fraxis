#include "Timer.hpp"

uint32_t Timer::GetTimeInMs()
{
    uint32_t time = 0;
    if (instance)
    {
        time = instance->GetTimeInMs();
    }
    return time;
}
