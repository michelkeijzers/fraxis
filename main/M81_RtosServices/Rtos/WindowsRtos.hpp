#pragma once

#include "Rtos.hpp"
#include <cstdint>

namespace M81
{
    namespace RtosQueue
    {
        class RtosQueue;
    }

    namespace RtosTask
    {
        class RtosTask;
    }
}

namespace M81::Rtos
{
    class WindowsRtos : public Rtos
    {
    public:
        WindowsRtos() = default;
        ~WindowsRtos() = default;

        RtosTask::RtosTask* CreateTask(
            TaskFunction_t taskFunction,
            const char* const name,
            uint32_t stackSize,
            uint8_t priority,
            uint8_t core,
            void* param) override;

        RtosQueue::RtosQueue* CreateQueue(
            uint32_t queueLength,
            uint32_t itemSize) override;
    };
}
