#ifdef ESP_PLATFORM

#include "EspRtosQueue.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

EspRtosQueue::EspRtosQueue(
    uint32_t queueLength, 
    uint32_t itemSize) 
:   RtosQueue()
{
    _handle = xQueueCreate(queueLength, itemSize);
    Assert::IsNotNullptr(Types::ETaskId::System, _handle, "_handle queue");
}

EspRtosQueue::~EspRtosQueue()
{
}

/// @brief  Sends a message.
/// @param itemToQueue 
/// @param msToWait 
/// @return Returns true if a message was successfully sent, or false when it was not succesfully sent (queue full).
/// In the latter case check against errQUEUE_FULL (== pdFALSE) was the result.
bool EspRtosQueue::Send(
    const void* itemToQueue, 
    uint32_t msToWait)
{
    BaseType_t result = xQueueSend(_handle, itemToQueue, pdMS_TO_TICKS(msToWait));
    return (result == pdPASS);
}

/// @brief Receives a message.
/// @param buffer  
/// @param msToWait 
/// @return Returns true if a message was successfully received, false when no message was received (timeout or queue
/// empty).
bool EspRtosQueue::Receive(
    void* item, 
    uint32_t msToWait)
{

    BaseType_t result = xQueueReceive(_handle, item, pdMS_TO_TICKS(msToWait));
    return (result == pdPASS);
}

bool EspRtosQueue::Peek(
    void* item, 
    uint32_t ticksToWait)
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

#endif // ESP_PLATFORM
