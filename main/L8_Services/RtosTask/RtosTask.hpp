#pragma once

#include <cstdint>

class RtosQueue;

class RtosTask
{
public:
    typedef void (*TaskFunction_t)(void*);

    RtosTask();
    virtual ~RtosTask();
    
    virtual void Start() = 0;

    virtual bool DelayTask(uint32_t ms) = 0;
    virtual uint32_t GetTaskTickCount() = 0;
};
