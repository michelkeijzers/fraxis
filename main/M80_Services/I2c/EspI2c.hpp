// @file EspI2c.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#pragma once

#include "I2c.hpp"

namespace M80::I2c
{
    class EspI2c : public I2c
    {
    public:
        EspI2c() = default;

        EspI2c(
            const EspI2c&) = delete;
        EspI2c& operator=(
            const EspI2c&) = delete;
        EspI2c(
            EspI2c&&) = delete;
        EspI2c& operator=(
            EspI2c&&) = delete;

        ~EspI2c() override = default;

    private:
        bool IsValidPort(
            uint8_t port) override;

        esp_err_t ParamConfig(
            uint8_t port,
            uint8_t sdaPin,
            uint8_t sclPin,
            uint32_t frequency) override;

        esp_err_t DriverInstall(
            uint8_t port) override;

        esp_err_t MasterWriteToDevice(
            uint8_t port,
            uint8_t deviceAddress,
            const uint8_t* data,
            size_t length,
            uint32_t timeoutInMs) override;

        esp_err_t MasterReadFromDevice(
            uint8_t port,
            uint8_t deviceAddress,
            uint8_t* data,
            size_t length,
            uint32_t timeoutInMs) override;

        void* CmdLinkCreate() override;

        void CmdLinkDelete(
            void* cmd) override;

        esp_err_t MasterStart(
            void* cmd) override;

        esp_err_t MasterStop(
            void* cmd) override;

        esp_err_t MasterWriteDeviceAddress(
            void* cmd,
            uint8_t deviceAddress) override;

        esp_err_t MasterWriteRegisterAddress(
            void* cmd,
            uint8_t registerAddress) override;

        esp_err_t MasterWriteByte(
            void* cmd,
            uint8_t byteToWrite) override;

        esp_err_t MasterReadByte(
            void* cmd,
            uint8_t* byteToRead) override;

        esp_err_t MasterWrite(
            void* cmd,
            const uint8_t* data,
            size_t length) override;

        esp_err_t MasterRead(
            void* cmd,
            uint8_t* data,
            size_t length) override;

        esp_err_t MasterCmdBegin(
            uint8_t port,
            void* cmd,
            uint32_t timeoutInMs) override;
    };
}

#endif
