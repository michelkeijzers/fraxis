#ifdef ESP_PLATFORM

#pragma once

#include "Nvs.hpp"
#include "nvs_flash.h"
#include "nvs.h"

class EspNvs : public Nvs
{
public:
    EspNvs();
    ~EspNvs();

private:
    bool Initialize() override;
    bool WriteString(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        const std::string& value) override;
    bool ReadString(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        std::string& value) override;
    bool WriteUint8(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint8_t value) override;
    bool ReadUint8(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint8_t& value) override;
    bool WriteUint16(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint16_t value) override;
    bool ReadUint16(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint16_t& value) override;
    bool WriteUint32(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint32_t value) override;
    bool ReadUint32(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint32_t& value) override;
    bool WriteBlob(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        const uint8_t* data,
        size_t length) override;
    bool ReadBlob(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint8_t* data,
        size_t& length) override;
    bool EraseKey(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key) override;
    bool EraseNamespace(
        const std::string& partition,
        const std::string& namespaceName) override;

private:
    esp_err_t Open(
        const std::string& partition,
        const std::string& namespaceName,
        nvs_mode_t mode,
        nvs_handle_t& handle);
};

#endif // ESP_PLATFORM
