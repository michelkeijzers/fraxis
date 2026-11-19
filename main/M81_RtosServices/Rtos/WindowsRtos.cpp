// @file WindowsRtos.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "../RtosTask/WindowsRtosTask.hpp"
#include "../RtosQueue/WindowsRtosQueue.hpp"
#include "WindowsRtos.hpp"
#include "windows.h" // NOSONAR S3806 non portable path
#include <thread>
#include <memory>

namespace M81::Rtos
{
    WindowsRtos::WindowsRtos(
        M90::Assert::IAssert& assert)
    :
        Rtos(assert)
    {
        // No actions required
    }

    RtosTask::IRtosTask* WindowsRtos::CreateTask(
        TaskFunction_t taskFunction, // NOSONAR Task Function
        const char* const /* name */,
        uint32_t /* stackSize */,
        uint8_t /* priority */,
        uint8_t /* core */,
        void* param, // NOSONAR: S5008: void *
        M90::Assert::IAssert& assert) 
    {
        auto task = std::make_unique<RtosTask::WindowsRtosTask>(assert, taskFunction, param);
        return task.release(); // NOSONAR S5025
    }

    RtosQueue::IRtosQueue* WindowsRtos::CreateQueue(
        uint32_t queueLength,
        uint32_t itemSize)
    {
        auto queue = std::make_unique<RtosQueue::WindowsRtosQueue>(
            GetAssert(), queueLength, itemSize);
        return queue.release(); // NOSONAR S5025
    }
}
