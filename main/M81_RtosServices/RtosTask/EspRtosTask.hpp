// @file EspRtosTask.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#pragma once

#include "RtosTask.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace M81::RtosTask
{
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
}

#endif // ESP_PLATFORM
