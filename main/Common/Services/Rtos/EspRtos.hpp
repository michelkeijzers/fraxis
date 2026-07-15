#if !defined(_WIN32) && !defined(_WIN64)

#pragma once

#include "Rtos.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class RtosTask;
class RtosQueue;

class EspRtos : public Rtos
{
public:
    ~EspRtos() = default;

    RtosTask* CreateTask(TaskFunction_t taskFunction, const char* const name, 
        uint32_t stackSize, uint8_t priority, uint8_t core, void* param) override;

    RtosQueue*  CreateQueue(uint32_t queueLength, uint32_t itemSize) override;
};

#endif
