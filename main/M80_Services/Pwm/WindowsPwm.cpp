// @file WindowsPwm.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "WindowsPwm.hpp"

namespace M80::Pwm
{
    WindowsPwm::WindowsPwm()
    {}

    esp_err_t WindowsPwm::ConfigTimer()
    {
        return ESP_OK;
    }

    esp_err_t WindowsPwm::LedcStop()
    {
        return ESP_OK;
    }

    esp_err_t WindowsPwm::AdjustFrequency()
    {
        return ESP_OK;
    }

    esp_err_t WindowsPwm::AdjustDutyCycle()
    {
        return ESP_OK;
    }
}
