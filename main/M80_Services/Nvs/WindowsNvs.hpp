#pragma once

#include "Nvs.hpp"

#include <cstdint>
#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>

class WindowsNvs : public Nvs
{
public:
    WindowsNvs() = default;
    virtual ~WindowsNvs() = default;

    bool Open(
        EReadWriteMode) override;

    bool ReadStringWhileInReadOnlyMode(
        std::string_view key,
        std::string& value) override;
    
    bool WriteStringWhileInReadWriteMode(
        std::string_view key,
        std::string_view value);
        
    bool ReadUint8WhileInReadOnlyMode(
        std::string_view key,
        uint8_t& value);

    bool WriteUint8WhileInReadWriteMode(
        std::string_view key,
        uint8_t value);

    bool ReadUint16WhileInReadOnlyMode(
        std::string_view key,
        uint16_t& value);

    bool WriteUint16WhileInReadWriteMode(
        std::string_view key,
        uint16_t value);

    bool ReadUint32WhileInReadOnlyMode(
        std::string_view key,
        uint32_t& value);

    bool WriteUint32WhileInReadWriteMode(
        std::string_view key,
        uint32_t value);

    bool ReadBlobWhileInReadOnlyMode(
        std::string_view key,
        uint8_t* data,
        size_t& length);

    bool WriteBlobWhileInReadWriteMode(
        std::string_view key,
        const uint8_t* data,
        size_t length);

    bool EraseKey(
        std::string_view key) override;

    bool EraseNamespace() override;

    void Close() override;
    bool CommitAndClose() override;

protected:
    bool FlashInit(
        bool& needsFlashErase) override;

    bool FlashErase() override;

private:
    std::filesystem::path GetBasePath() const;
    std::filesystem::path GetKeyPath(
        std::string_view key) const;
};
