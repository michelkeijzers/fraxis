#pragma once

#include <cstdint>

class RtosTask;

class Rtos
{
public:
    typedef void (*TaskFunction_t)(void*);

    virtual RtosTask* CreateTask(TaskFunction_t taskFunction, const char* const name, 
        uint32_t stackSize, uint8_t priority, uint8_t core, void* param) = 0;
};
