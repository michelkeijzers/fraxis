// @file Nvs.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "INvs.hpp"

namespace M80::Nvs
{
    class Nvs : public INvs
    {
    public:
        Nvs();

        Nvs(
            const Nvs&) = delete;

        Nvs& operator=(
            const Nvs&) = delete;

        Nvs(
            Nvs&&) = delete;

        Nvs& operator=(
            Nvs&&) = delete;

        virtual ~Nvs() = default;

        virtual esp_err_t Initialize() override;

        virtual void SetPartition(
            std::string_view partition) override;

        virtual void SetNamespace(
            std::string_view namespaceName) override;

        esp_err_t ReadString(
            std::string_view key,
            std::string& value) override;

        esp_err_t WriteString(
            std::string_view key,
            std::string_view value) override;

        esp_err_t ReadUint8(
            std::string_view key,
            uint8_t& value) override;

        esp_err_t WriteUint8(
            std::string_view key,
            uint8_t value);

        esp_err_t ReadUint16(
            std::string_view key,
            uint16_t& value);

        esp_err_t WriteUint16(
            std::string_view key,
            uint16_t value);

        esp_err_t ReadUint32(
            std::string_view key,
            uint32_t& value);

        esp_err_t WriteUint32(
            std::string_view key,
            uint32_t value);

        esp_err_t ReadBlob(
            std::string_view key,
            uint8_t* data,
            size_t& length);

        esp_err_t WriteBlob(
            std::string_view key,
            const uint8_t* data,
            size_t length);

        virtual esp_err_t EraseKey(
            std::string_view key) = 0;

        virtual esp_err_t EraseNamespace() = 0;

        virtual esp_err_t Close() = 0;

        /// <summary>
            /// Only needed when writing.
            /// </summary>
        virtual esp_err_t CommitAndClose() = 0;

    protected:
        enum class EReadWriteMode
        {
            ReadOnly,
            ReadWrite
        };

        virtual esp_err_t FlashInit(
            bool& needsFlashErase);

        virtual esp_err_t FlashInit() = 0;

        virtual esp_err_t FlashErase() = 0;

        [[nodiscard]] std::string_view GetPartition() const;

        [[nodiscard]] std::string_view GetNamespace() const;

        EReadWriteMode GetReadWriteMode() const;

        void SetReadWriteMode(
            EReadWriteMode mode);

        bool GoingFromReadOnlyToReadWrite(
            EReadWriteMode mode) const;

        virtual esp_err_t Open(
            EReadWriteMode mode) = 0;

        virtual esp_err_t ReadStringWhileInReadOnlyMode(
            std::string_view key,
            std::string& value) = 0;

        virtual esp_err_t WriteStringWhileInReadWriteMode(
            std::string_view key,
            std::string_view value) = 0;

        virtual esp_err_t ReadUint8WhileInReadOnlyMode(
            std::string_view key,
            uint8_t& value) = 0;

        virtual esp_err_t WriteUint8WhileInReadWriteMode(
            std::string_view key,
            uint8_t value) = 0;

        virtual esp_err_t ReadUint16WhileInReadOnlyMode(
            std::string_view key,
            uint16_t& value) = 0;

        virtual esp_err_t WriteUint16WhileInReadWriteMode(
            std::string_view key,
            uint16_t value) = 0;

        virtual esp_err_t ReadUint32WhileInReadOnlyMode(
            std::string_view key,
            uint32_t& value) = 0;

        virtual esp_err_t WriteUint32WhileInReadWriteMode(
            std::string_view key,
            uint32_t value) = 0;

        virtual esp_err_t ReadBlobWhileInReadOnlyMode(
            std::string_view key,
            uint8_t* data,
            size_t& length) = 0;

        virtual esp_err_t WriteBlobWhileInReadWriteMode(
            std::string_view key,
            const uint8_t* data,
            size_t length) = 0;

    private:
        std::string _partition;

        std::string _namespaceName;

        EReadWriteMode _readWriteMode;
    };
}
