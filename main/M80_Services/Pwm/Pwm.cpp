// @file Pwm.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Pwm.hpp"

namespace M80::Pwm
{
    Pwm::Pwm()
        :
        _pin(0),
        _frequency(0),
        _dutyCycle(0.0f),
        _started(0)
    {
    }

    void Pwm::Config(
        uint8_t pin,
        uint32_t frequency,
        float dutyCycle)
    {
        _pin = pin;
        _frequency = frequency;
        _dutyCycle = dutyCycle;
    }

    bool Pwm::GetStarted() const
    {
        return _started;
    }

    uint8_t Pwm::GetPin() const
    {
        return _pin;
    }

    uint32_t Pwm::GetFrequency() const
    {
        return _frequency;
    }

    esp_err_t Pwm::SetFrequency(
        uint32_t frequency)
    {
        esp_err_t err = ESP_OK;
        if (frequency != _frequency)
        {
            _frequency = frequency;
            err = AdjustFrequency();
        }

        return err;
    }

    float Pwm::GetDutyCycle() const
    {
        return _dutyCycle;
    }

    esp_err_t Pwm::SetDutyCycle(
        float dutyCycle)
    {
        esp_err_t err = ESP_OK;
        if (dutyCycle != _dutyCycle)
        {
            _dutyCycle = dutyCycle;
            err = AdjustDutyCycle();
        }

        return err;
    }

    esp_err_t Pwm::Start()
    {
        return ConfigTimer();
    }

    esp_err_t Pwm::Stop()
    {
        if (!_started)
        {
            return ESP_OK;
        }

        return LedcStop();
    }
}
