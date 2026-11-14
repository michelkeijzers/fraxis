// @file Gpio.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#ifdef ESP_PLATFORM
#include "esp_err.h"
#else
#include  "../WindowsEspErr.hpp"
#endif 

#include <cstdint>

namespace M80::Gpio
{
    class IGpio
    {
    public:
        IGpio() = default;

        IGpio(
            const IGpio&) = delete;
        
        IGpio& operator=(
            const IGpio&) = delete;
        
        IGpio(
            IGpio&&) = delete;
        
        IGpio& operator=(
            IGpio&&) = delete;

        virtual ~IGpio() = default;

        virtual esp_err_t ConfigAsOutput(
            uint8_t pin) = 0;

        virtual esp_err_t ConfigAsInterruptInput(
            uint8_t pin) = 0;

        virtual esp_err_t SetLevel(
            uint8_t pin,
            bool level) = 0;

       virtual esp_err_t InstallIsrService() = 0;

        virtual esp_err_t AddInterruptHandler(
            int pin,
            void (*interruptCallbackFunction)(void*),
            void* arg) = 0;

        virtual void DelayUs(
            uint32_t microSeconds) = 0;
    };
}
