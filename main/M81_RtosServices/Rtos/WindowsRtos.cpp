#include "../RtosTask/WindowsRtosTask.hpp"
#include "../RtosQueue/WindowsRtosQueue.hpp"
#include "WindowsRtos.hpp"
#include "windows.h" // NOSONAR S3806 non portable path
#include <thread>
#include <memory>

RtosTask* WindowsRtos::CreateTask(
    TaskFunction_t taskFunction, // NOSONAR Task Function
    const char* const /* name */,
    uint32_t /* stackSize */,
    uint8_t /* priority */,
    uint8_t /* core */,
    void* param) // NOSONAR: S5008: void *
{
    auto task = std::make_unique<WindowsRtosTask>(taskFunction, param);
    return task.release(); // NOSONAR S5025
}

RtosQueue* WindowsRtos::CreateQueue(
    uint32_t queueLength,
    uint32_t itemSize)
{
    auto queue = std::make_unique<WindowsRtosQueue>(queueLength, itemSize);
    return queue.release(); // NOSONAR S5025
}
