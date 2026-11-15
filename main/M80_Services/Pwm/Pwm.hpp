// @file Pwm.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IPwm.hpp" 

namespace M80::Pwm
{
    class Pwm : public IPwm
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
            float dutyCycle) override;

        uint8_t GetPin() const override;

        uint32_t GetFrequency() const override;

        esp_err_t SetFrequency(
            uint32_t frequency) override;

        float GetDutyCycle() const override;

        esp_err_t SetDutyCycle(
            float dutyCycle) override;

        bool GetStarted() const override;

        esp_err_t Start() override;

        esp_err_t Stop() override;

    private:
        uint8_t _pin;

        uint32_t _frequency;

        float _dutyCycle;

        bool _started;
    };
}
