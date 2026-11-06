#ifdef ESP_PLATFORM

#pragma once

#include "Nvs.hpp"
#include "nvs_flash.h"
#include "nvs.h"
#include <string>
#include <cstdint>

class EspNvs : public Nvs
{
public:
    EspNvs();

    EspNvs(const EspNvs&) = delete;
    EspNvs& operator=(const EspNvs&) = delete;
    EspNvs(EspNvs&&) = delete;
    EspNvs& operator=(EspNvs&&) = delete;

    ~EspNvs() override = default;

private:
    bool FlashInit(
        bool& needsFlashErase);

    bool FlashErase();

    bool ReadStringWhileInReadOnlyMode(
        std::string_view key,
        std::string& value) override;

    bool WriteStringWhileInReadWriteMode(
        std::string_view key,
        std::string_view value) override;

    bool WriteUint8WhileInReadWriteMode(
        std::string_view key,
        uint8_t value) override;

    bool ReadUint8WhileInReadOnlyMode(
        std::string_view key,
        uint8_t& value) override;

    bool WriteUint16WhileInReadWriteMode(
        std::string_view key,
        uint16_t value) override;

    bool ReadUint16WhileInReadOnlyMode(
        std::string_view key,
        uint16_t& value) override;

    bool WriteUint32WhileInReadWriteMode(
        std::string_view key,
        uint32_t value) override;

    bool ReadUint32WhileInReadOnlyMode(
        std::string_view key,
        uint32_t& value) override;

    bool WriteBlobWhileInReadWriteMode(
        std::string_view key,
        const uint8_t* data,
        size_t length) override;

    bool ReadBlobWhileInReadOnlyMode(
        std::string_view key,
        uint8_t* data,
        size_t& length) override;

    bool EraseKey(
        std::string_view key) override;

    bool EraseNamespace() override;

    void Close() override;

    bool CommitAndClose() override;

    nvs_open_mode_t ReadWriteModeToNvsReadWriteMode(
        EReadWriteMode mode);

    bool Open(
        EReadWriteMode mode);

    nvs_handle_t _handle;
};

#endif // ESP_PLATFORM
