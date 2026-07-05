#include "EspRtosQueue.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

EspRtosQueue::EspRtosQueue(uint32_t queueLength, uint32_t itemSize) 
{
    _queue = xQueueCreate(queueLength, itemSize);
}


bool EspRtosQueue::Send(const void* itemToQueue, uint32_t msToWait)
{
    BaseType_t result = xQueueSend(_queue, itemToQueue, pdMS_TO_TICKS(msToWait));
    return (result == pdPASS);
}

bool EspRtosQueue::Receive(void* buffer, uint32_t msToWait)
{

    BaseType_t result = xQueueReceive(_queue, buffer, pdMS_TO_TICKS(msToWait));
    return (result == pdPASS);
}