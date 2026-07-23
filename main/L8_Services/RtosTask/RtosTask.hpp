#pragma once

#include <cstdint>

class RtosQueue;

class RtosTask
{
public:
    typedef void (*TaskFunction_t)(void*);

    virtual ~RtosTask() = default;
    
    virtual void Start() = 0;

    virtual bool DelayTask(uint32_t ms) = 0;
    virtual uint32_t GetTaskTickCount() = 0;

    virtual RtosQueue* CreateQueue(uint32_t queueLength, uint32_t itemSize) = 0;
};
