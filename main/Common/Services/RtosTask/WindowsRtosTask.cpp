#include "WindowsRtosTask.hpp"
#include "windows.h"
#include <chrono>

WindowsRtosTask::WindowsRtosTask()
{}

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

bool WindowsRtosTask::CreateQueue(uint32_t queueLength, uint32_t itemSize)
{
    return true;
}
