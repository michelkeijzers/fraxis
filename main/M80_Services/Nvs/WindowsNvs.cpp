// @file WindowsNvs.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "WindowsNvs.hpp"

#include <cstring>
#include <filesystem>
#include <fstream>

namespace M80::Nvs
{
    esp_err_t WindowsNvs::FlashInit()
    {
        std::filesystem::create_directories(GetBasePath());
        return ESP_OK;
    }

    esp_err_t WindowsNvs::FlashErase()
    {
        // No action needed.
        return ESP_OK;
    }

    esp_err_t WindowsNvs::Open(
        EReadWriteMode)
    {
        // No action needed.
        return ESP_OK;
    }

    esp_err_t WindowsNvs::ReadStringWhileInReadOnlyMode(
        std::string_view key,
        std::string& value)
    {
        value.clear();

        auto path = GetKeyPath(key);
        if (!std::filesystem::exists(path))
        {
            return false;
        }

        const auto size = static_cast<size_t>(std::filesystem::file_size(path));
        value.resize(size);
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
        {
            return false;
        }

        file.read(value.data(), static_cast<std::streamsize>(size));
        return static_cast<bool>(file);
    }

    esp_err_t WindowsNvs::WriteStringWhileInReadWriteMode(
        std::string_view key,
        std::string_view value)
    {
        return WriteBlob(key, reinterpret_cast<const uint8_t*>(value.data()), value.size()); // NOSONAR
    }

    esp_err_t WindowsNvs::ReadUint8WhileInReadOnlyMode(
        std::string_view key,
        uint8_t& value)
    {
        size_t length = sizeof(value);
        if (esp_err_t err = ReadBlob(key, &value, length); err != ESP_OK)
        {
            return err;
        }
        if (length == sizeof(value))
        {
            return ESP_OK;
        }
        return ESP_FAIL;
    }

    esp_err_t WindowsNvs::WriteUint8WhileInReadWriteMode(
        std::string_view key,
        uint8_t value)
    {
        return WriteBlob(key, &value, sizeof(value));
    }

    esp_err_t WindowsNvs::ReadUint16WhileInReadOnlyMode(
        std::string_view key,
        uint16_t& value)
    {
        size_t length = sizeof(value);
        if (esp_err_t err = ReadBlob(key, reinterpret_cast<uint8_t*>(&value), length); err != ESP_OK)
        {
            return err;
        }
        if (length == sizeof(value))
        {
            return ESP_OK;
        }
        return ESP_FAIL;
    }

    esp_err_t WindowsNvs::WriteUint16WhileInReadWriteMode(
        std::string_view key,
        uint16_t value)
    {
        return WriteBlob(key, reinterpret_cast<const uint8_t*>(&value), sizeof(value)); // NOSONAR
    }

    esp_err_t WindowsNvs::ReadUint32WhileInReadOnlyMode(
        std::string_view key,
        uint32_t& value)
    {
        size_t length = sizeof(value);
        if (esp_err_t err = ReadBlob(key, reinterpret_cast<uint8_t*>(&value), length); err != ESP_OK)
        {
            return err;
        }
        if (length == sizeof(value))
        {
            return ESP_OK;
        }
        return ESP_FAIL;
    }

    esp_err_t WindowsNvs::WriteUint32WhileInReadWriteMode(
        std::string_view key,
        uint32_t value)
    {
        return WriteBlob(key, reinterpret_cast<const uint8_t*>(&value), sizeof(value)); // NOSONAR
    }

    esp_err_t WindowsNvs::ReadBlobWhileInReadOnlyMode(
        std::string_view key,
        uint8_t* data,
        size_t& length)
    {
        auto path = GetKeyPath(key);
        if (!std::filesystem::exists(path))
        {
            length = 0;
            return ESP_ERR_NVS_NOT_FOUND;
        }

        const auto fileSize = static_cast<size_t>(std::filesystem::file_size(path));
        if (length < fileSize)
        {
            length = fileSize;
            return ESP_ERR_NVS_INVALID_LENGTH;
        }

        std::ifstream file(path, std::ios::binary);
        if (!file.is_open())
        {
            return ESP_FAIL;
        }

        file.read(reinterpret_cast<char*>(data), static_cast<std::streamsize>(fileSize)); // NOSONAR

        if (!file)
        {
            return ESP_FAIL;
        }

        length = fileSize;
        return ESP_OK;
    }

    esp_err_t WindowsNvs::WriteBlobWhileInReadWriteMode(
        std::string_view key,
        const uint8_t* data,
        size_t length)
    {
        std::filesystem::create_directories(GetBasePath());
        std::ofstream file(GetKeyPath(key), std::ios::binary | std::ios::trunc);
        if (!file.is_open())
        {
            return ESP_FAIL;
        }

        file.write(
            reinterpret_cast<const char*>(data),
            static_cast<std::streamsize>(length)); // NOSONAR
        return static_cast<bool>(file) ? ESP_OK : ESP_FAIL;
    }

    esp_err_t WindowsNvs::EraseKey(
        std::string_view key)
    {
        return std::filesystem::remove(GetKeyPath(key)) ? ESP_OK : ESP_FAIL;
    }

    esp_err_t WindowsNvs::EraseNamespace()
    {
        std::error_code ec;

        std::filesystem::remove_all(GetBasePath(), ec);
        return !ec ? ESP_OK : ESP_FAIL;
    }

    esp_err_t WindowsNvs::Close()
    {
        // No action needed.
        return ESP_OK;
    }

    esp_err_t WindowsNvs::CommitAndClose()
    {
        // No action needed.
        return ESP_OK;
    }

    std::filesystem::path WindowsNvs::GetBasePath() const
    {
        return std::filesystem::path("Storage") /
            std::string(GetPartition()) / std::string(GetNamespace());
    }

    std::filesystem::path WindowsNvs::GetKeyPath(
        std::string_view key) const
    {
        return GetBasePath() / std::string(key);
    }
}
