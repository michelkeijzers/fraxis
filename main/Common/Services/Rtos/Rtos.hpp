#pragma once

#include <cstdint>

class Rtos
{
public:
    typedef void (*TaskFunction_t)(void*);

    virtual bool CreateTask(TaskFunction_t taskFunction, const char* const name, 
        uint32_t stackSize, uint8_t priority, uint8_t core) = 0;
};
