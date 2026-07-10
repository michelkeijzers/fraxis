#if !defined(_WIN32) && !defined(_WIN64)

#include "../RtosTask/EspRtosTask.hpp"
#include "EspRtos.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Intellisense gives an error for xTaskCreatePinnedToCore.
#ifdef __INTELLISENSE__
    #define TASK_CREATE(taskFunction, name, stackSize, parameter, priority, taskHandle, core) 0 // -> xTaskCreatePinnedToCore
#else
    #define TASK_CREATE xTaskCreatePinnedToCore
#endif

RtosTask* EspRtos::CreateTask(TaskFunction_t taskFunction, const char* const name,
    uint32_t stackSize, uint8_t priority, uint8_t core, void* param)
{
    TaskHandle_t taskHandle;

    //#ifndef __INTELLISENSE__
    //TODO: result unused
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
    //TODO: Assert on result
    return new EspRtosTask(taskHandle);
}

#endif