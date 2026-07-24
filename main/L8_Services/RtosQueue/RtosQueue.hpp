#pragma once

#include <cstdint>

class RtosQueue
{
public:
    RtosQueue() {}
    virtual ~RtosQueue() = default;

    virtual bool Send(const void* itemToQueue, uint32_t msToWait) = 0;
    virtual bool Receive(void* item, uint32_t msToWait) = 0;

    virtual bool Peek(void* item, uint32_t ticksToWait) = 0;
    virtual uint32_t MessagesWaiting() const = 0;
    virtual uint32_t SpacesAvailable() const = 0;

};
