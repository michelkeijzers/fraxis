// @file EspRtos.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#include "EspRtos.hpp"
#include "../RtosTask/EspRtosTask.hpp"
#include "../RtosQueue/EspRtosQueue.hpp"
#include "../../M80_Services/Intellisense/EspBypass.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

namespace M81::Rtos
{
    RtosTask::RtosTask* EspRtos::CreateTask(
        TaskFunction_t taskFunction,
        const char* name,
        uint32_t stackSize,
        uint8_t priority,
        uint8_t core,
        void* param /* = nullptr */)
    {
        TaskHandle_t taskHandle;

        //#ifndef __INTELLISENSE__
        BaseType_t result = TASK_CREATE(
            taskFunction,        // Task entry function
            name,                // Task name
            stackSize / 4,       // Stack size in words (not bytes!)
            param,               // Parameter
            priority,            // Priority
            &taskHandle,         // Task handle (optional)
            core                 // Core ID (0 or 1)
        );
        M90::Assert::Assert::Equals(Types::ETaskId::System, result, pdPASS, "Failed to create task");
        //#endif

        return new RtosTask::EspRtosTask(taskHandle);
    }

    RtosQueue::RtosQueue* EspRtos::CreateQueue(
        uint32_t queueLength,
        uint32_t itemSize)
    {
        return new RtosQueue::EspRtosQueue(queueLength, itemSize);
    }
}

#endif // ESP_PLATFORM
