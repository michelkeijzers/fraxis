#pragma once

#include "../../DeviceDriver.hpp"
#include <cstdint>

class Pwm;
class RtosTask;

class BuzzerDeviceDriver : public DeviceDriver
{
public:
    BuzzerDeviceDriver();
    ~BuzzerDeviceDriver() = default;

    Pwm& GetPwm();
    void SetPwm(
        Pwm& pwm);

    void SetConfiguration(
        uint8_t pwmPin);

    void SetRtosTask(
        RtosTask& rtosTask);

    void SetFrequency(
        uint32_t frequency);

    void Start();
    void Stop();

private:
    uint8_t _pwmPin;
    uint32_t _frequency;

    Pwm* _pwm;
    RtosTask* _rtosTask;
};
