// @file EspI2sService.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#pragma once

#include "I2sService.hpp"
#include "driver/i2s.h"

namespace M90::Assert
{
    class IAssert;
}

namespace M80::I2s
{
    class EspI2sService : public I2sService
    {
    public:
        explicit EspI2sService(
            M90::Assert::IAssert& assert);

        EspI2sService(
            const EspI2sService&) = delete;

        EspI2sService& operator=(
            const EspI2sService&) = delete;

        EspI2sService(
            EspI2sService&&) = delete;

        EspI2sService& operator=(
            EspI2sService&&) = delete;

        ~EspI2sService() override;

        bool ParamConfig(
            uint8_t port,
            uint8_t bclkPin,
            uint8_t wsPin,
            uint8_t dinPin,
            uint8_t doutPin,
            uint32_t sampleRate,
            uint16_t bitsPerSample,
            uint8_t channels) override;

        bool DriverInstall(
            uint8_t port) override;

        bool Start(
            uint8_t port) override;

        bool Stop(
            uint8_t port) override;

        size_t Read(
            uint8_t port,
            void* buffer,
            size_t length,
            uint32_t timeoutInMs) override;

        size_t Write(
            uint8_t port,
            const void* buffer,
            size_t length,
            uint32_t timeoutInMs) override;

        bool SetClock(
            uint8_t port,
            uint32_t sampleRate) override;

    private:
        i2s_config_t _config;

        i2s_pin_config_t _pinConfig;

        uint8_t _channels;
    };
}

#endif // ESP_PLATFORM
