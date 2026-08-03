#ifdef ESP_PLATFORM

#pragma once

#include "RtosTask.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class EspRtosTask : public RtosTask
{
public:
    EspRtosTask(
        TaskHandle_t taskHandle);
    ~EspRtosTask();
    
    void Start() override {};

    bool DelayTask(
        uint32_t ms) override;
    uint32_t GetTaskTickCount() override;

private:
    TaskHandle_t _taskHandle;
};

#endif // ESP_PLATFORM
