#if !defined(_WIN32) && !defined(_WIN64)

#pragma once

#include "RtosTask.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class EspRtosTask : public RtosTask
{
public:
    EspRtosTask();
    ~EspRtosTask() = default;
    
    bool CreateTask(TaskFunction_t taskFunction, const char* const name, 
        uint32_t stackSize, uint8_t priority, uint8_t core) override;
    bool DelayTask(uint32_t ms) override;
    uint32_t GetTaskTickCount() override;

    bool CreateQueue(uint32_t queueLength, uint32_t itemSize) override;
};

#endif
