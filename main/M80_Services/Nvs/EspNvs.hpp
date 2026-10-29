#ifdef ESP_PLATFORM

#pragma once

#include "Nvs.hpp"
#include "nvs_flash.h"
#include "nvs.h"

class EspNvs : public Nvs
{
public:
    EspNvs();

    EspNvs(const EspNvs&) = delete;
    EspNvs& operator=(const EspNvs&) = delete;
    EspNvs(EspNvs&&) = delete;
    EspNvs& operator=(EspNvs&&) = delete;

    ~EspNvs() override;

private:
    bool Initialize() override;

    bool WriteString(
        std::string_view key,
        std::string_view value) override;

    bool ReadString(
        std::string_view key,
        std::string& value) override;

    bool WriteUint8(
        std::string_view key,
        uint8_t value) override;

    bool ReadUint8(
        std::string_view key,
        uint8_t& value) override;

    bool WriteUint16(
        std::string_view key,
        uint16_t value) override;

    bool ReadUint16(
        std::string_view key,
        uint16_t& value) override;

    bool WriteUint32(
        std::string_view key,
        uint32_t value) override;

    bool ReadUint32(
        std::string_view key,
        uint32_t& value) override;

    bool WriteBlob(
        std::string_view key,
        const uint8_t* data,
        size_t length) override;

    bool ReadBlob(
        std::string_view key,
        uint8_t* data,
        size_t& length) override;

    bool EraseKey(
        std::string_view key) override;

    bool EraseNamespace() override;

    void Close() override;

    bool CommitAndClose() override;

    esp_err_t Open(
        nvs_open_mode_t mode);

    nvs_handle_t _handle;
    nvs_open_mode_t _mode;
};

#endif // ESP_PLATFORM
