#pragma once

#include "RtosTask.hpp"
#include <cstdint>
#include <thread>

class WindowsRtosTask : public RtosTask
{
public:
    WindowsRtosTask(
        TaskFunction_t func, 
        void* param);
    ~WindowsRtosTask() = default;

    void Start() override;

    bool DelayTask(
        uint32_t ms) override;
    uint32_t GetTaskTickCount() override;

private:
    void PreciseSleep(double milliseconds) const;

    TaskFunction_t _func;
    void* _param; // NOSONAR: ESP32 prefers void*
    std::jthread _thread;
    bool _started;
};
