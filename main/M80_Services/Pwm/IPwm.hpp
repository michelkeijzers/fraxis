// @file Pwm.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#ifdef ESP_PLATFORM
#include "esp_err.h"
#else
#include  "../WindowsEspErr.hpp"
#endif

#include "../../M80_Services/IService.hpp"
#include <cstdint>

namespace M80::Pwm
{
    class IPwm
    {
    public:
        virtual ~IPwm() = default;

        virtual void Config(
            uint8_t pin,
            uint32_t frequency,
            float dutyCycle) = 0;

        virtual esp_err_t ConfigTimer() = 0;

        virtual uint8_t GetPin() const = 0;

        virtual uint32_t GetFrequency() const = 0;

        virtual esp_err_t SetFrequency(uint32_t frequency) = 0;

        virtual esp_err_t AdjustFrequency() = 0;

        virtual float GetDutyCycle() const = 0;

        virtual esp_err_t SetDutyCycle(
            float dutyCycle) = 0;

        virtual esp_err_t AdjustDutyCycle() = 0;

        virtual bool GetStarted() const = 0;

        virtual esp_err_t Start() = 0;

        virtual esp_err_t Stop() = 0;

        virtual esp_err_t LedcStop() = 0;
    };
}
