#include "WindowsRtos.hpp"
#include "windows.h"

WindowsRtos::WindowsRtos()
{}

bool WindowsRtos::CreateTask(TaskFunction_t taskFunction, const char* const name,
    uint32_t stackSize, uint8_t priority, uint8_t core)
{
    return true;
}
