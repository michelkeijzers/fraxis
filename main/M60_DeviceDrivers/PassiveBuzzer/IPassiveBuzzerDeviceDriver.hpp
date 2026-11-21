// @file IPassiveBuzzerDeviceDriver.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../IDeviceDriver.hpp"
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

namespace M60::I2s
{
    class IPassiveBuzzerDeviceDriver
    {
    public:
        virtual ~IPassiveBuzzerDeviceDriver() = default;

        [[nodiscard]] virtual M80::Pwm::IPwm& GetPwm() = 0;

        virtual void SetPwm(
            M80::Pwm::IPwm& pwm) = 0;

        virtual void SetConfiguration(
            uint8_t pwmPin) = 0;

        virtual void SetRtosTask(
            M81::RtosTask::IRtosTask& rtosTask) = 0;

        virtual void SetFrequency(
            uint32_t frequency) = 0;

        virtual void Start() = 0;

        virtual void Stop() = 0;
    };
}