// @file INvs.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#ifdef ESP_PLATFORM
#include "esp_err.h"
#else
#include  "../WindowsEspErr.hpp"
#endif
#include <cstdint>
#include <cstddef>
#include <string>
#include <string_view>

namespace M80::Nvs
{
    class INvs
    {
      public:
        INvs() = default;

        INvs(const INvs &) = delete;

        INvs &operator=(const INvs &) = delete;

        INvs(INvs &&) = delete;

        INvs &operator=(INvs &&) = delete;

        virtual ~INvs() = default;

        virtual esp_err_t Initialize() = 0;

        virtual void SetPartition(
            std::string_view partition) = 0;

        virtual void SetNamespace(
            std::string_view namespaceName) = 0;

        virtual esp_err_t ReadString(
            std::string_view key,
            std::string &value) = 0;

        virtual esp_err_t WriteString(
            std::string_view key, 
            std::string_view value) = 0;

        virtual esp_err_t ReadUint8(
            std::string_view key, 
            uint8_t &value) = 0;

        virtual esp_err_t WriteUint8(
            std::string_view key, 
            uint8_t value) = 0;

        virtual esp_err_t ReadUint16(
            std::string_view key, 
            uint16_t &value) = 0;

        virtual esp_err_t WriteUint16(
            std::string_view key, 
            uint16_t value) = 0;

        virtual esp_err_t ReadUint32(
            std::string_view key, 
            uint32_t &value) = 0;

        virtual esp_err_t WriteUint32(
            std::string_view key, 
            uint32_t value) = 0;

        virtual esp_err_t ReadBlob(
            std::string_view key, 
            uint8_t *data,
            size_t &length) = 0;

        virtual esp_err_t WriteBlob(
            std::string_view key, 
            const uint8_t *data,
            size_t length) = 0;

        virtual esp_err_t EraseKey(
            std::string_view key) = 0;

        virtual esp_err_t EraseNamespace() = 0;

        virtual esp_err_t Close() = 0;

        /// <summary>
        /// Only needed when writing.
        /// </summary>
        virtual esp_err_t CommitAndClose() = 0;
    };
}
