// @file IRtos.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

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
    class IRtos
    {
    public:
        using TaskFunction_t = void (*)(void*);

        IRtos() = default;

        IRtos(
            const IRtos&) = delete;

        IRtos& operator=(
            const IRtos&) = delete;

        IRtos(
            IRtos&&) = delete;
        
        IRtos& operator=(
            IRtos&&) = delete;

        virtual ~IRtos() = default;

        virtual M81::RtosTask::IRtosTask* CreateTask(
            TaskFunction_t taskFunction,
            const char* name,
            uint32_t stackSize,
            uint8_t priority,
            uint8_t core,
            void* param = nullptr) = 0;

        virtual M81::RtosQueue::IRtosQueue* CreateQueue(
            uint32_t queueLength,
            uint32_t itemSize) = 0;
    };
}
