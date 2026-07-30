#if !defined(_WIN32) && !defined(_WIN64)

#include "../RtosTask/EspRtosTask.hpp"
#include "../RtosQueue/EspRtosQueue.hpp"
#include "EspRtos.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "../../L8_Services/Intellisense/EspBypass.hpp"
#include "../../L9_Utilities/Assert/Assert.hpp"

EspRtos::EspRtos() 
{
}

EspRtos::~EspRtos() 
{
}

RtosTask* EspRtos::CreateTask(TaskFunction_t taskFunction, const char* const name,
    uint32_t stackSize, uint8_t priority, uint8_t core, void* param /* = nullptr */ )
{
    TaskHandle_t taskHandle;

    //#ifndef __INTELLISENSE__
    BaseType_t result = TASK_CREATE(
        taskFunction,        // Task entry function
        name,                // Task name
        stackSize / 4,       // Stack size in words (not bytes!)
        param,             // Parameter
        priority,            // Priority
        &taskHandle,             // Task handle (optional)
        core                 // Core ID (0 or 1)
    );
    Assert::Equals(result, pdPASS, "Failed to create task");
    //#endif
    
    return new EspRtosTask(taskHandle);
}

RtosQueue* EspRtos::CreateQueue(uint32_t queueLength, uint32_t itemSize)
{
    return new EspRtosQueue(queueLength, itemSize); 
}

#endif
