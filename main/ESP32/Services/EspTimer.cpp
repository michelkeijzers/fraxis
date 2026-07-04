#include "EspTimer.hpp"
#include "esp_timer.h"

EspTimer::EspTimer() 
{
}

uint32_t EspTimer::GetTimeInMs()
{
    return esp_timer_get_time() / 1000;
}
