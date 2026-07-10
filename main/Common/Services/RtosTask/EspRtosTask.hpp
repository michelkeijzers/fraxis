#if !defined(_WIN32) && !defined(_WIN64)

#pragma once

#include "RtosTask.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class EspRtosTask : public RtosTask
{
public:
    EspRtosTask(TaskHandle_t taskHandle);
    ~EspRtosTask() = default;
    
    void Start() override {};

    bool DelayTask(uint32_t ms) override;
    uint32_t GetTaskTickCount() override;

    bool CreateQueue(uint32_t queueLength, uint32_t itemSize) override;

private:
    TaskHandle_t _taskHandle;
};

#endif
