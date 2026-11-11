#pragma once

#include "Pwm.hpp"
#include <cstdint>

class WindowsPwm : public Pwm
{
public:
    WindowsPwm();
    ~WindowsPwm() = default;

    esp_err_t ConfigTimer() override;

    esp_err_t LedcStop() override;

    esp_err_t AdjustFrequency() override;

    esp_err_t AdjustDutyCycle() override;
};
