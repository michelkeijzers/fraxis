// @file EspNvs.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#ifdef ESP_PLATFORM

#pragma once

#include "Nvs.hpp"
#include "nvs_flash.h"
#include "nvs.h"
#include <string>
#include <cstdint>

namespace M80::Nvs
{
    class EspNvs : public Nvs
    {
    public:
        EspNvs();

        EspNvs(
            const EspNvs&) = delete;

        EspNvs& operator=(
            const EspNvs&) = delete;

        EspNvs(
            EspNvs&&) = delete;

        EspNvs& operator=(
            EspNvs&&) = delete;

        ~EspNvs() override = default;

    private:
        esp_err_t FlashInit();

        esp_err_t FlashErase();

        esp_err_t ReadStringWhileInReadOnlyMode(
            std::string_view key,
            std::string& value) override;

        esp_err_t WriteStringWhileInReadWriteMode(
            std::string_view key,
            std::string_view value) override;

        esp_err_t WriteUint8WhileInReadWriteMode(
            std::string_view key,
            uint8_t value) override;

        esp_err_t ReadUint8WhileInReadOnlyMode(
            std::string_view key,
            uint8_t& value) override;

        esp_err_t WriteUint16WhileInReadWriteMode(
            std::string_view key,
            uint16_t value) override;

        esp_err_t ReadUint16WhileInReadOnlyMode(
            std::string_view key,
            uint16_t& value) override;

        esp_err_t WriteUint32WhileInReadWriteMode(
            std::string_view key,
            uint32_t value) override;

        esp_err_t ReadUint32WhileInReadOnlyMode(
            std::string_view key,
            uint32_t& value) override;

        esp_err_t WriteBlobWhileInReadWriteMode(
            std::string_view key,
            const uint8_t* data,
            size_t length) override;

        esp_err_t ReadBlobWhileInReadOnlyMode(
            std::string_view key,
            uint8_t* data,
            size_t& length) override;

        esp_err_t EraseKey(
            std::string_view key) override;

        esp_err_t EraseNamespace() override;

        esp_err_t Close() override;

        esp_err_t CommitAndClose() override;

        nvs_open_mode_t ReadWriteModeToNvsReadWriteMode(
            EReadWriteMode mode);

        esp_err_t Open(
            EReadWriteMode mode);

        nvs_handle_t _handle;
    };
}

#endif // ESP_PLATFORM
