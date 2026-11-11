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

    esp_err_t Open(
        EReadWriteMode) override;

    esp_err_t ReadStringWhileInReadOnlyMode(
        std::string_view key,
        std::string& value) override;
    
    esp_err_t WriteStringWhileInReadWriteMode(
        std::string_view key,
        std::string_view value) override;
        
    esp_err_t ReadUint8WhileInReadOnlyMode(
        std::string_view key,
        uint8_t& value) override;

    esp_err_t WriteUint8WhileInReadWriteMode(
        std::string_view key,
        uint8_t value) override;

    esp_err_t ReadUint16WhileInReadOnlyMode(
        std::string_view key,
        uint16_t& value) override;

    esp_err_t WriteUint16WhileInReadWriteMode(
        std::string_view key,
        uint16_t value) override;

    esp_err_t ReadUint32WhileInReadOnlyMode(
        std::string_view key,
        uint32_t& value) override;

    esp_err_t WriteUint32WhileInReadWriteMode(
        std::string_view key,
        uint32_t value) override;

    esp_err_t ReadBlobWhileInReadOnlyMode(
        std::string_view key,
        uint8_t* data,
        size_t& length) override;

    esp_err_t WriteBlobWhileInReadWriteMode(
        std::string_view key,
        const uint8_t* data,
        size_t length) override;

    esp_err_t EraseKey(
        std::string_view key) override;

    esp_err_t EraseNamespace() override;

    esp_err_t Close() override;
    esp_err_t CommitAndClose() override;

protected:
    esp_err_t FlashInit() override;

    esp_err_t FlashErase() override;

private:
    std::filesystem::path GetBasePath() const;
    std::filesystem::path GetKeyPath(
        std::string_view key) const;
};
