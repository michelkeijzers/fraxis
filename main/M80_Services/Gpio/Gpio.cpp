// @file Gpio.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Gpio.hpp"

namespace M80::Gpio
{
    /* static */ bool Gpio::_isIsrServiceInstalled = false;

    esp_err_t Gpio::InstallIsrService()
    {
        if (!_isIsrServiceInstalled)
        {
            esp_err_t result = InstallIsrServiceWhenNotInstalledYet();
            if (result == ESP_OK)
            {
                _isIsrServiceInstalled = true;
                return ESP_OK;
            }
            return result;
        }
        return ESP_OK;
    }
}
