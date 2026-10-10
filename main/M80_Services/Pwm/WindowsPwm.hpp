#pragma once

#include "Pwm.hpp"
#include <cstdint>

class WindowsPwm : public Pwm
{
public:
    WindowsPwm();
    ~WindowsPwm() = default;

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
    uint8_t _pin;
    uint32_t _frequency;
    float _dutyCycle;
    bool _started;
};
