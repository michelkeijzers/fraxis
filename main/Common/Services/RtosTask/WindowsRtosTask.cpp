#include "WindowsRtosTask.hpp"
#include "../RtosQueue/WindowsRtosQueue.hpp"
#include "windows.h"
#include <chrono>
#include <thread>

WindowsRtosTask::WindowsRtosTask(TaskFunction_t func, void* param)
    : _func(func), _param(param), _started(false)
{
}

WindowsRtosTask::~WindowsRtosTask()
{
    if (_thread.joinable())
    {
        _thread.detach();
    }
}

void WindowsRtosTask::Start()
{
    if (_started)
    {
        return;
    }

    _started = true;
    _thread = std::thread([this]() {
        _func(_param);
        });
}

bool WindowsRtosTask::DelayTask(uint32_t ms)
{
	Sleep(ms);
    return true;
}

uint32_t WindowsRtosTask::GetTaskTickCount()
{
    using namespace std::chrono;
    return (uint32_t)duration_cast<milliseconds>(
        steady_clock::now().time_since_epoch()
    ).count();
}

RtosQueue* WindowsRtosTask::CreateQueue(uint32_t queueLength, uint32_t itemSize)
{
    return new WindowsRtosQueue(queueLength, itemSize);
}
