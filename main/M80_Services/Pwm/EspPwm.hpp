#ifdef ESP_PLATFORM

#pragma once

#include "Pwm.hpp"
#include "driver/ledc.h"

class EspPwm : public Pwm
{
public:
    EspPwm();
    ~EspPwm();

    bool Config(
        uint8_t pin,
        uint32_t frequency,
        float dutyCycle) override;

    bool Start() override;

    bool Stop() override;

    bool SetFrequency(
        uint32_t frequency) override;

    bool SetDutyCycle(
        float dutyCycle) override;

private:
    ledc_channel_t _channel;
    uint8_t _pin;
    uint32_t _frequency;
    float _dutyCycle;
    bool _started;
};

#endif // ESP_PLATFORM
