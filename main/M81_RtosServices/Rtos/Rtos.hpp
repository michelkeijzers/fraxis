#pragma once

#include <cstdint>

class RtosTask;
class RtosQueue;

class Rtos
{
public:
    using TaskFunction_t = void (*)(void*);

    Rtos();

    Rtos(const Rtos&) = delete;
    Rtos& operator=(const Rtos&) = delete;
    Rtos(Rtos&&) = delete;
    Rtos& operator=(Rtos&&) = delete;

    virtual ~Rtos();

    virtual RtosTask* CreateTask(
        TaskFunction_t taskFunction, 
        const char* name, 
        uint32_t stackSize,
        uint8_t priority,
        uint8_t core, 
        void* param = nullptr) = 0;

    virtual RtosQueue* CreateQueue(
        uint32_t queueLength, 
        uint32_t itemSize) = 0;
};
