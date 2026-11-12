// @file I2c.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#ifdef ESP_PLATFORM
#include "esp_err.h"
#else
#include  "../WindowsEspErr.hpp"
#endif 
#include <cstdint>
#include <stddef.h>

namespace M80::I2c
{
    class I2c
    {
    public:
        I2c() = default;

        I2c(
            const I2c&) = delete;

        I2c& operator=(
            const I2c&) = delete;

        I2c(
            I2c&&) = delete;

        I2c& operator=(
            I2c&&) = delete;

        virtual ~I2c() = default;

        virtual bool IsValidPort(
            uint8_t port) = 0;

        virtual esp_err_t ParamConfig(
            uint8_t port,
            uint8_t sdaPin,
            uint8_t sclPin,
            uint32_t frequency) = 0;

        virtual esp_err_t DriverInstall(
            uint8_t port) = 0;

        virtual esp_err_t MasterWriteToDevice(
            uint8_t port,
            uint8_t deviceAddress,
            const uint8_t* data,
            size_t length,
            uint32_t timeoutInMs) = 0;

        virtual esp_err_t MasterReadFromDevice(
            uint8_t port, uint8_t deviceAddress,
            uint8_t* data,
            size_t length,
            uint32_t timeoutInMs) = 0;

        virtual void* CmdLinkCreate() = 0; // NOSONAR: ESP expects void*

        virtual void CmdLinkDelete(
            void* cmd) = 0; // NOSONAR: ESP expects void*

        virtual esp_err_t MasterStart(
            void* cmd) = 0; // NOSONAR: ESP expects void*

        virtual esp_err_t MasterWriteDeviceAddress(
            void* cmd, // NOSONAR: ESP expects void*
            uint8_t deviceAddress) = 0;

        virtual esp_err_t MasterWriteRegisterAddress(
            void* cmd,  // NOSONAR: ESP expects void*
            uint8_t registerAddress) = 0;

        virtual esp_err_t MasterWriteByte(
            void* cmd, // NOSONAR: ESP expects void*
            uint8_t byteToWrite) = 0;

        virtual esp_err_t MasterReadByte(
            void* cmd, // NOSONAR: ESP expects void*
            uint8_t* byteToRead) = 0;

        virtual esp_err_t MasterWrite(
            void* cmd, // NOSONAR: ESP expects void*
            const uint8_t* data,
            size_t length) = 0;

        virtual esp_err_t MasterRead(
            void* cmd, // NOSONAR: ESP expects void*
            uint8_t* data,
            size_t length) = 0;

        virtual esp_err_t MasterStop(
            void* cmd) = 0; // NOSONAR: ESP expects void*

        virtual esp_err_t MasterCmdBegin(
            uint8_t port,
            void* cmd,  // NOSONAR: ESP expects void*
            uint32_t timeoutInMs) = 0;
    };
}
