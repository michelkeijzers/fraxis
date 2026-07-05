#include "EspRtos.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

EspRtos::EspRtos() 
{
}

bool EspRtos::CreateTask(TaskFunction_t taskFunction, const char* const name,
    uint32_t stackSize, uint8_t priority, uint8_t core)
{
    BaseType_t result = xTaskCreatePinnedToCore(
        taskFunction,        // Task entry function
        name,                // Task name
        stackSize / 4,       // Stack size in words (not bytes!)
        nullptr,             // Parameter
        priority,            // Priority
        nullptr,             // Task handle (optional)
        core                 // Core ID (0 or 1)
    );

    return (result == pdPASS);
}

bool EspRtos::DelayTask(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
    return true;
}

uint32_t EspRtos::GetTaskTickCount()
{
    return (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);
}

bool EspRtos::CreateQueue(uint32_t queueLength, uint32_t itemSize)
{
    return xQueueCreate(queueLength, itemSize);
}
