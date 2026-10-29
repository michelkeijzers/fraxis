#pragma once

#include "../../DeviceDriver.hpp"
#include <cstdint>

class Pwm;
class RtosTask;

class BuzzerDeviceDriver : public DeviceDriver
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    BuzzerDeviceDriver();

    BuzzerDeviceDriver(const BuzzerDeviceDriver&) = delete;
    BuzzerDeviceDriver& operator=(const BuzzerDeviceDriver&) = delete;
    BuzzerDeviceDriver(BuzzerDeviceDriver&&) = delete;
    BuzzerDeviceDriver& operator=(BuzzerDeviceDriver&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~BuzzerDeviceDriver() override;

    [[nodiscard]] bool IsInitialized() const override;
    void Initialize() override;

    [[nodiscard]] Pwm& GetPwm();
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
