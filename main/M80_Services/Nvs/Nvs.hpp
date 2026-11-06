// @file Nvs.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <string_view>

class Nvs
{
public:
    Nvs();

    Nvs(const Nvs&) = delete;

    Nvs& operator=(const Nvs&) = delete;

    Nvs(Nvs&&) = delete;

    Nvs& operator=(Nvs&&) = delete;

    virtual ~Nvs() = default;

    virtual bool Initialize();

    virtual void SetPartition(
        std::string_view partition);

    virtual void SetNamespace(
        std::string_view namespaceName);

    bool ReadString(
        std::string_view key,
        std::string& value);

    bool WriteString(
        std::string_view key,
        std::string_view value);

    bool ReadUint8(
        std::string_view key,
        uint8_t& value);

    bool WriteUint8(
        std::string_view key,
        uint8_t value);

    bool ReadUint16(
        std::string_view key,
        uint16_t& value);

    bool WriteUint16(
        std::string_view key,
        uint16_t value);

    bool ReadUint32(
        std::string_view key,
        uint32_t& value);

    bool WriteUint32(
        std::string_view key,
        uint32_t value);

    bool ReadBlob(
        std::string_view key,
        uint8_t* data,
        size_t& length);
    
    bool WriteBlob(
        std::string_view key,
        const uint8_t* data,
        size_t length);

    virtual bool EraseKey(
        std::string_view key) = 0;

    virtual bool EraseNamespace() = 0;

    virtual void Close() = 0;
/// <summary>
    /// Only needed when writing.
    /// </summary>
    virtual bool CommitAndClose() = 0;
    
protected:    
    enum class EReadWriteMode
    {
        ReadOnly, 
        ReadWrite 
    };

    virtual bool FlashInit(
        bool& needsFlashErase) = 0;
    virtual bool FlashErase() = 0;

    [[nodiscard]] std::string_view GetPartition() const;
    [[nodiscard]] std::string_view GetNamespace() const;

    EReadWriteMode GetReadWriteMode() const;
    void SetReadWriteMode(
        EReadWriteMode mode);

    bool GoingFromReadOnlyToReadWrite(
        EReadWriteMode mode) const;

    virtual bool Open(
        EReadWriteMode mode) = 0;

    virtual bool ReadStringWhileInReadOnlyMode(
        std::string_view key,
        std::string& value) = 0;

    virtual bool WriteStringWhileInReadWriteMode(
        std::string_view key,
        std::string_view value) = 0;

    virtual bool ReadUint8WhileInReadOnlyMode(
        std::string_view key,
        uint8_t& value) = 0;

    virtual bool WriteUint8WhileInReadWriteMode(
        std::string_view key,
        uint8_t value) = 0;

    virtual bool ReadUint16WhileInReadOnlyMode(
        std::string_view key,
        uint16_t& value) = 0;

    virtual bool WriteUint16WhileInReadWriteMode(
        std::string_view key,
        uint16_t value) = 0;

    virtual bool ReadUint32WhileInReadOnlyMode(
        std::string_view key,
        uint32_t& value) = 0;

    virtual bool WriteUint32WhileInReadWriteMode(
        std::string_view key,
        uint32_t value) = 0;

    virtual bool ReadBlobWhileInReadOnlyMode(
        std::string_view key,
        uint8_t* data,
        size_t& length) = 0;

    virtual bool WriteBlobWhileInReadWriteMode(
        std::string_view key,
        const uint8_t* data,
        size_t length) = 0;

private:
    std::string _partition;
    std::string _namespaceName;
    EReadWriteMode _readWriteMode;
};
