#pragma once

#include <cstdint>

class RtosTask
{
public:
    typedef void (*TaskFunction_t)(void*);

    virtual ~RtosTask() = default;
    
    virtual void Start() = 0;

    virtual bool DelayTask(uint32_t ms) = 0;
    virtual uint32_t GetTaskTickCount() = 0;

    virtual bool CreateQueue(uint32_t queueLength, uint32_t itemSize) = 0;
};
