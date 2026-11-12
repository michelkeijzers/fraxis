// @file Pwm.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#ifdef ESP_PLATFORM
#include "esp_err.h"
#else
#include  "../WindowsEspErr.hpp"
#endif

#include <cstdint>

namespace M80::Pwm
{
    class Pwm
    {
    public:
        Pwm();

        Pwm(
            const Pwm&) = delete;

        Pwm& operator=(
            const Pwm&) = delete;

        Pwm(
            Pwm&&) = delete;

        Pwm& operator=(
            Pwm&&) = delete;

        virtual ~Pwm() = default;

        void Config(
            uint8_t pin,
            uint32_t frequency,
            float dutyCycle);

        virtual esp_err_t ConfigTimer() = 0;

        uint8_t GetPin() const;

        uint32_t GetFrequency() const;

        esp_err_t SetFrequency(
            uint32_t frequency);

        virtual esp_err_t AdjustFrequency() = 0;

        float GetDutyCycle() const;

        esp_err_t SetDutyCycle(
            float dutyCycle);

        virtual esp_err_t AdjustDutyCycle() = 0;

        bool GetStarted() const;

        esp_err_t Start();

        esp_err_t Stop();

        virtual esp_err_t LedcStop() = 0;

    private:
        uint8_t _pin;

        uint32_t _frequency;

        float _dutyCycle;

        bool _started;
    };
}
