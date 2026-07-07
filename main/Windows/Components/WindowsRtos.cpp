#include "WindowsRtos.hpp"
#include "windows.h"
#include <chrono>

WindowsRtos::WindowsRtos()
{}

bool WindowsRtos::CreateTask(TaskFunction_t taskFunction, const char* const name,
    uint32_t stackSize, uint8_t priority, uint8_t core)
{
    return true;
}

bool WindowsRtos::DelayTask(uint32_t ms)
{
	Sleep(ms);
    return true;
}

uint32_t WindowsRtos::GetTaskTickCount()
{
    using namespace std::chrono;
    return (uint32_t)duration_cast<milliseconds>(
        steady_clock::now().time_since_epoch()
    ).count();
}

bool WindowsRtos::CreateQueue(uint32_t queueLength, uint32_t itemSize)
{
    return true;
}
