#if !defined(_WIN32) && !defined(_WIN64)

#include "EspRtosTask.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

EspRtosTask::EspRtosTask(TaskHandle_t taskHandle) 
: _taskHandle(taskHandle)
{
}

bool EspRtosTask::DelayTask(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
    return true;
}

uint32_t EspRtosTask::GetTaskTickCount()
{
    return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

bool EspRtosTask::CreateQueue(uint32_t queueLength, uint32_t itemSize)
{
    return xQueueCreate(queueLength, itemSize);
}

#endif