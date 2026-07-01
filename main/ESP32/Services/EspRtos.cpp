#include "EspRtos.hpp"

void EspRtos::vTaskDelay(int ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}