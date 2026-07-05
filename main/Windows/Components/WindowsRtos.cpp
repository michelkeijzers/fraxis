#include "WindowsRtos.hpp"
#include "windows.h"

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
    return true;
}

bool WindowsRtos::CreateQueue(uint32_t queueLength, uint32_t itemSize)
{
    return true;
}
