#pragma once

#include <cstdint>

class Pwm
{
public:
    Pwm() = default;
    virtual ~Pwm() = default;

    virtual bool Config(
        uint8_t pin,
        uint32_t frequency,
        float dutyCycle) = 0;

    virtual bool Start() = 0;

    virtual bool Stop() = 0;

    virtual bool SetFrequency(
        uint32_t frequency) = 0;

    virtual bool SetDutyCycle(
        float dutyCycle) = 0;
};
