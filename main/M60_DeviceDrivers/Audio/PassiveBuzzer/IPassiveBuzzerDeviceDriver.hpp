#pragma once

#include "../../IDeviceDriver.hpp"
#include <cstdint>

namespace M80::Pwm
{
    class IPwm;
}

namespace M81::RtosTask
{
    class IRtosTask;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M90::StringUtilities
{
    class IStringUtilities;
}

namespace M60::Audio
{
    class IPassiveBuzzerDeviceDriver : IDeviceDriver
    {
    public:
        virtual ~IPassiveBuzzerDeviceDriver();

        [[nodiscard]] bool IsInitialized() const;

        void Initialize(;

        [[nodiscard]] M80::Pwm::IPwm& GetPwm();

        void SetPwm(
            M80::Pwm::IPwm& pwm);

        void SetConfiguration(
            uint8_t pwmPin);

        void SetRtosTask(
            M81::RtosTask::IRtosTask& rtosTask);

        void SetFrequency(
            uint32_t frequency);

        void Start();
        void Stop();

    private:
        uint8_t _pwmPin;
        uint32_t _frequency;

        M80::Pwm::IPwm* _pwm;
        M81::RtosTask::IRtosTask* _rtosTask;
    };
}