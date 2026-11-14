// @file Rtos.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IRtos.hpp"
#include <cstdint>

namespace M81
{
    namespace RtosQueue
    {
        class IRtosQueue;
    }

    namespace RtosTask
    {
        class IRtosTask;
    }
}

namespace M81::Rtos
{
    class Rtos : public IRtos
    {
    public:
        using TaskFunction_t = void (*)(void*);

        Rtos() = default;

        Rtos(
            const Rtos&) = delete;

        Rtos& operator=(
            const Rtos&) = delete;

        Rtos(
            Rtos&&) = delete;
        
        Rtos& operator=(
            Rtos&&) = delete;

        virtual ~Rtos() = default;

        virtual M81::RtosTask::IRtosTask* CreateTask(
            TaskFunction_t taskFunction,
            const char* name,
            uint32_t stackSize,
            uint8_t priority,
            uint8_t core,
            void* param = nullptr) override = 0;

        virtual M81::RtosQueue::IRtosQueue* CreateQueue(
            uint32_t queueLength,
            uint32_t itemSize) override = 0;
    };
}
