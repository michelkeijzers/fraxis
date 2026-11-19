// @file Gpio.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IGpio.hpp"
#include "../Service.hpp"

namespace M90::Assert
{
    class IAssert;
}

namespace M80::Gpio
{
    class Gpio : public Service, public IGpio
    {
    public:
        explicit Gpio(
            M90::Assert::IAssert& assert);

        Gpio(
            const Gpio&) = delete;
        
        Gpio& operator=(
            const Gpio&) = delete;
        
        Gpio(
            Gpio&&) = delete;
        
        Gpio& operator=(
            Gpio&&) = delete;

        virtual ~Gpio() = default;

        esp_err_t InstallIsrService() override;

    protected:
        virtual esp_err_t InstallIsrServiceWhenNotInstalledYet() = 0;

    private:
        static bool _isIsrServiceInstalled;
    };
}
