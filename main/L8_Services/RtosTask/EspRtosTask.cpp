#ifdef ESP_PLATFORM

#include "EspRtosTask.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "../RtosQueue/EspRtosQueue.hpp"

EspRtosTask::EspRtosTask(
    TaskHandle_t taskHandle) 
: _taskHandle(taskHandle)
{
}

EspRtosTask::~EspRtosTask()
{
    vTaskDelete(_taskHandle);
}

bool EspRtosTask::DelayTask(
    uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
    return true;
}

uint32_t EspRtosTask::GetTaskTickCount()
{
    return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

#endif // ESP_PLATFORM
