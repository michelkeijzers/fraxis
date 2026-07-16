#if !defined(_WIN32) && !defined(_WIN64)

#include "../RtosTask/EspRtosTask.hpp"
#include "../RtosQueue/EspRtosQueue.hpp"
#include "EspRtos.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "../../Services/Intellisense/EspBypass.hpp"

RtosTask* EspRtos::CreateTask(TaskFunction_t taskFunction, const char* const name,
    uint32_t stackSize, uint8_t priority, uint8_t core, void* param)
{
    TaskHandle_t taskHandle;

    //#ifndef __INTELLISENSE__
    //TODO: result unused, assert
    BaseType_t result = TASK_CREATE(
        taskFunction,        // Task entry function
        name,                // Task name
        stackSize / 4,       // Stack size in words (not bytes!)
        nullptr,             // Parameter
        priority,            // Priority
        &taskHandle,             // Task handle (optional)
        core                 // Core ID (0 or 1)
    );
    //#endif
    
    return new EspRtosTask(taskHandle);
}

RtosQueue* EspRtos::CreateQueue(uint32_t queueLength, uint32_t itemSize)
{
    return new EspRtosQueue(queueLength, itemSize); 
}

#endif