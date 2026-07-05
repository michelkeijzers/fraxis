#pragma once

#include <cstdint>

class IRtosQueue
{
public:
    virtual ~IRtosQueue() = default;

    virtual bool Send(const void* itemToQueue, uint32_t msToWait) = 0;
    virtual bool Receive(void* buffer, uint32_t msToWait) = 0;
};
