#if !defined(_WIN32) && !defined(_WIN64)

#pragma once

#include <cstdint>
#include "RtosQueue.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

class EspRtosQueue : public RtosQueue 
{
public:
    EspRtosQueue(uint32_t queueLength, uint32_t itemSize);
    ~EspRtosQueue() = default;
    
    bool Send(const void* itemToQueue, uint32_t msToWait) override;
    bool Receive(void* item, uint32_t msToWait) override;

    bool Peek(void* item, uint32_t ticksToWait) override;
    uint32_t MessagesWaiting() const override;
    uint32_t SpacesAvailable() const override;
    
private:
    QueueHandle_t _handle;
};

#endif