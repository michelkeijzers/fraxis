#if !defined(_WIN32) && !defined(_WIN64)

#pragma once

#include <cstdint>
#include "Rtos.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class EspRtos : public Rtos
{
public:
    EspRtos();
    ~EspRtos() = default;
    
    bool CreateTask(TaskFunction_t taskFunction, const char* const name, 
        uint32_t stackSize, uint8_t priority, uint8_t core) override;
};

#endif
