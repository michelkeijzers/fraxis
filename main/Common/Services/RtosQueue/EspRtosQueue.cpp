#if !defined(_WIN32) && !defined(_WIN64)

#include "EspRtosQueue.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

EspRtosQueue::EspRtosQueue(uint32_t queueLength, uint32_t itemSize) 
: RtosQueue()
{
    _handle = xQueueCreate(queueLength, itemSize);
}


bool EspRtosQueue::Send(const void* itemToQueue, uint32_t msToWait)
{
    BaseType_t result = xQueueSend(_handle, itemToQueue, pdMS_TO_TICKS(msToWait));
    return (result == pdPASS);
}

bool EspRtosQueue::Receive(void* item, uint32_t msToWait)
{

    BaseType_t result = xQueueReceive(_handle, item, pdMS_TO_TICKS(msToWait));
    return (result == pdPASS);
}

bool EspRtosQueue::Peek(void* item, uint32_t ticksToWait)
{
    return xQueuePeek(_handle, item, ticksToWait) == pdTRUE;
}

uint32_t EspRtosQueue::MessagesWaiting() const
{
    return uxQueueMessagesWaiting(_handle);
}

uint32_t EspRtosQueue::SpacesAvailable() const
{
    return uxQueueSpacesAvailable(_handle);
}
#endif
