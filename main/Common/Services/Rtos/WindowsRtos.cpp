#include "../RtosTask/WindowsRtosTask.hpp"
#include "WindowsRtos.hpp"
#include "windows.h"
#include <thread>

WindowsRtos::WindowsRtos()
{}

RtosTask* WindowsRtos::CreateTask(TaskFunction_t taskFunction, const char* const name,
    uint32_t stackSize, uint8_t priority, uint8_t core, void* param)
{
    //std::thread thread([taskFunction, param]() { taskFunction(param); });
    return new WindowsRtosTask(taskFunction, param);
}
