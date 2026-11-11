#ifdef ESP_PLATFORM

#pragma once

#include "Pwm.hpp"
#include "driver/ledc.h"
#include <cstdint>

class EspPwm : public Pwm
{
public:
    EspPwm();

    EspPwm(
        const EspPwm&) = delete;

    EspPwm& operator=(
        const EspPwm&) = delete;

    EspPwm(
        EspPwm&&) = delete;

    EspPwm& operator=(
        EspPwm&&) = delete;

    ~EspPwm() override;

    esp_err_t ConfigTimer() override;

    esp_err_t LedcStop() override;

    esp_err_t AdjustFrequency() override;

    esp_err_t AdjustDutyCycle() override;

private:
    ledc_channel_t _channel;
};

#endif // ESP_PLATFORM
