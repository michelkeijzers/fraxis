// @file WindowsPwm.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "Pwm.hpp"
#include <cstdint>

namespace M90::Assert
{
    class IAssert;
}

namespace M80::Pwm
{
    class WindowsPwm : public Pwm
    {
    public:
        explicit WindowsPwm(
            M90::Assert::IAssert& assert);

        ~WindowsPwm() = default;

        esp_err_t ConfigTimer() override;

        esp_err_t LedcStop() override;

        esp_err_t AdjustFrequency() override;

        esp_err_t AdjustDutyCycle() override;
    };
}
