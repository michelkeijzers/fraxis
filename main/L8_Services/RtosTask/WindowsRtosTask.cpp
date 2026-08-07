#include "WindowsRtosTask.hpp"
#include "../RtosQueue/WindowsRtosQueue.hpp"
#include "../Rtos/WindowsRtos.hpp"
#include "../../L9_Utilities/Log/Log.hpp"
#include "Windows.h"
#include <chrono>
#include <thread>

WindowsRtosTask::WindowsRtosTask(
    TaskFunction_t func,
    void* param) // NOSONAR: ESP32 prefers void*
    : _func(func), _param(param), _started(false)
{
}

void WindowsRtosTask::Start()
{
    if (_started)
    {
        return;
    }

    _started = true;
    _thread = std::jthread([this]() {
        _func(_param);
        });
}

bool WindowsRtosTask::DelayTask(
    uint32_t ms)
{
    /// @todo : find better solution
    Sleep(ms <= 3 ? 3 : ms);
    // Alternative: busy wait with PreciseSleep
    return true;
}

void WindowsRtosTask::PreciseSleep(double milliseconds) const
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + std::chrono::duration<double, std::milli>(milliseconds);

    // Hybrid approach: Sleep for most of the time, then busy-wait
    if (milliseconds > 2.0) 
    {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(static_cast<long long>(milliseconds - 1)));
    }

    // Busy-wait for the remainder
    while (std::chrono::high_resolution_clock::now() < end) 
    {
        // Spin
    }
}

uint32_t WindowsRtosTask::GetTaskTickCount()
{
    using namespace std::chrono;
    return (uint32_t)duration_cast<milliseconds>(
        steady_clock::now().time_since_epoch()
    ).count();
}
