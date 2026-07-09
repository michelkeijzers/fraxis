#pragma once

#include <cstdint>

class RtosTask
{
public:
    typedef void (*TaskFunction_t)(void*);

    virtual ~RtosTask() = default;

    virtual bool CreateTask(TaskFunction_t taskFunction, const char* const name, 
        uint32_t stackSize, uint8_t priority, uint8_t core) = 0;
    virtual bool DelayTask(uint32_t ms) = 0;
    virtual uint32_t GetTaskTickCount() = 0;

    virtual bool CreateQueue(uint32_t queueLength, uint32_t itemSize) = 0;
};
