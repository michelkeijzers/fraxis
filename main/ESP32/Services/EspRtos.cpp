#include "EspRtos.hpp"

EspRtos::EspRtos() 
{
}


void EspRtos::TaskDelay(int ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}