#if !defined(_WIN32) && !defined(_WIN64)

#include "EspRtosQueue.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

EspRtosQueue::EspRtosQueue(uint32_t queueLength, uint32_t itemSize) 
{
    _queue = xQueueCreate(queueLength, itemSize);
    Assert::IsNotNull(_queue, "queue");
}

/// @brief  Sends a message.
/// @param itemToQueue 
/// @param msToWait 
/// @return Returns true if a message was successfully sent, or false when it was not succesfully sent (queue full).
/// In the latter case check against errQUEUE_FULL (== pdFALSE) was the result.
bool EspRtosQueue::Send(const void* itemToQueue, uint32_t msToWait)
{
    BaseType_t result = xQueueSend(_queue, itemToQueue, pdMS_TO_TICKS(msToWait));
    return (result == pdTRUE);
}

/// @brief Receives a message.
/// @param buffer  
/// @param msToWait 
/// @return Returns true if a message was successfully received, false when no message was received (timeout or queue
/// empty).
bool EspRtosQueue::Receive(void* buffer, uint32_t msToWait)
{

    BaseType_t result = xQueueReceive(_queue, buffer, pdMS_TO_TICKS(msToWait));
    return (result == pdTRUE);
}

#endif
