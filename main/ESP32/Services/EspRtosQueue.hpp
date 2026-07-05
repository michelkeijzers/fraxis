#pragma once

#include "../../Core/Services/IRtosQueue.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

class EspRtosQueue : public IRtosQueue 
{
public:
    EspRtosQueue(uint32_t queueLength, uint32_t itemSize);
    ~EspRtosQueue() = default;
    
    bool Send(const void* itemToQueue, uint32_t msToWait) override;
    bool Receive(void* buffer, uint32_t msToWait) override;

private:
    QueueHandle_t _queue;
};
