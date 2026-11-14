// @file EspRtos.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#pragma once

#include "Rtos.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace RtosTask
{
    class RtosTask;
}

namespace RtosQueue
{
    class RtosQueue;
}

namespace M81::Rtos
{
    class EspRtos : public Rtos
    {
    public:
        EspRtos() = default;

        EspRtos(
            const EspRtos&) = delete;

        EspRtos& operator=(
            const EspRtos&) = delete;

        EspRtos(
            EspRtos&&) = delete;

        EspRtos& operator=(
            EspRtos&&) = delete;

        ~EspRtos() override = default;

        RtosTask::IRtosTask* CreateTask(
            TaskFunction_t taskFunction,
            const char* name,
            uint32_t stackSize,
            uint8_t priority,
            uint8_t core,
            void* param = nullptr) override;

        RtosQueue::IRtosQueue* CreateQueue(
            uint32_t queueLength,
            uint32_t itemSize) override;
    };
}

#endif // ESP_PLATFORM
