// @file EspGpio.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#pragma once

#include "Gpio.hpp"

namespace M80::Gpio
{
    class EspGpio : public Gpio
    {
    public:
        EspGpio() = default;

        EspGpio(
            const EspGpio&) = delete;
        EspGpio& operator=(
            const EspGpio&) = delete;
        EspGpio(
            EspGpio&&) = delete;
        EspGpio& operator=(
            EspGpio&&) = delete;

        ~EspGpio() override = default;

    private:
        esp_err_t ConfigAsOutput(
            uint8_t pin) override;

        esp_err_t ConfigAsInterruptInput(
            uint8_t pin) override;

        esp_err_t SetLevel(
            uint8_t pin,
            bool level) override;

        esp_err_t AddInterruptHandler(
            int pin,
            void (*interruptCallbackFunction)(void*),
            void* arg) override;

        void DelayUs(uint32_t microSeconds) override;

        esp_err_t InstallIsrServiceWhenNotInstalledYet() override;
    };
}

#endif // ESP_PLATFORM
