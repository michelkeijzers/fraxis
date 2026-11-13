#pragma once

#include "../../DeviceDriver.hpp"
#include <cstdint>

namespace M80::Pwm
{
    class Pwm;
}

namespace M81::RtosTask
{
    class RtosTask;
}

namespace M60::Audio
{
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

        [[nodiscard]] M80::Pwm::Pwm& GetPwm();
        void SetPwm(
            M80::Pwm::Pwm& pwm);

        void SetConfiguration(
            uint8_t pwmPin);

        void SetRtosTask(
            M81::RtosTask::RtosTask& rtosTask);

        void SetFrequency(
            uint32_t frequency);

        void Start();
        void Stop();

    private:
        uint8_t _pwmPin;
        uint32_t _frequency;

        M80::Pwm::Pwm* _pwm;
        M81::RtosTask::RtosTask* _rtosTask;
    };
}