#pragma once

#include <cstdint>

class RtosTask;
class RtosQueue;

class Rtos
{
public:
    typedef void (*TaskFunction_t)(void*);

    virtual RtosTask* CreateTask(TaskFunction_t taskFunction, const char* const name, 
        uint32_t stackSize, uint8_t priority, uint8_t core, void* param = nullptr) = 0;
    virtual RtosQueue* CreateQueue(uint32_t queueLength, uint32_t itemSize) = 0;
};
