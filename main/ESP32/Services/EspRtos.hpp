#pragma once

#include "../../Core/Services/IRtos.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class EspRtos : public IRtos 
{
public:
    void vTaskDelay(int ms) override;
};
