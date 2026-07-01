#include "EspRtos.hpp"

EspRtos::EspRtos() 
{
}

EspRtos::~EspRtos() 
{
}

void EspRtos::vTaskDelay(int ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}