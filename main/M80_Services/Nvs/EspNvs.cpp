#ifdef ESP_PLATFORM

#include "EspNvs.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include "nvs_flash.h"
#include "nvs.h"
#include <string.h>
#include <vector>

EspNvs::EspNvs()
:
    _handle(0),
    _mode(NVS_READONLY)
{
}

EspNvs::~EspNvs()
{
}

bool EspNvs::Initialize()
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        Assert::IsTrue(
            Types::ETaskId::System, 
            nvs_flash_erase() == ESP_OK, 
            "Failed to erase NVS flash");
        err = nvs_flash_init();
    }
    Assert::IsTrue(
        Types::ETaskId::System, 
        err == ESP_OK, 
        "Failed to initialize NVS flash");
    return true;
}

esp_err_t EspNvs::Open(
    nvs_open_mode_t mode)
{
    // Make reading possible with NVS_READWRITE to prevent unnecessary nvs_open_from_partition 
    // calls.
    if ((_handle == 0) || ((_mode == NVS_READONLY) && (mode == NVS_READWRITE)))
    {
        return nvs_open_from_partition(
            GetPartition().data(), GetNamespace().data(), mode, &_handle);
    }
    return ESP_OK;
}

bool EspNvs::WriteString(
    const std::string_view key,
    const std::string_view value)
{
    Open(NVS_READWRITE);
    esp_err_t err = nvs_set_str(_handle, key.data(), value.data());
    return err == ESP_OK;
}

bool EspNvs::ReadString(
    const std::string_view key,
    std::string& value)
{
    Open(NVS_READONLY);
    size_t length = 0;
    esp_err_t err = nvs_get_str(_handle, key.data(), value.data(), &length);
    return err == ESP_OK;
}

bool EspNvs::WriteUint8(
    const std::string_view key,
    uint8_t value)
{
    Open(NVS_READWRITE);
    esp_err_t err = nvs_set_u8(_handle, key.data(), value);
    return err == ESP_OK;
}

bool EspNvs::ReadUint8(
    const std::string_view key,
    uint8_t& value)
{
    Open(NVS_READONLY);
    esp_err_t err = nvs_get_u8(_handle, key.data(), &value);
    return err == ESP_OK;
}

bool EspNvs::WriteUint16(
    const std::string_view key,
    uint16_t value)
{
    Open(NVS_READWRITE);
    esp_err_t err = nvs_set_u16(_handle, key.data(), value);
    return err == ESP_OK;
}

bool EspNvs::ReadUint16(
    const std::string_view key,
    uint16_t& value)
{
    Open(NVS_READONLY);
    esp_err_t err = nvs_get_u16(_handle, key.data(), &value);
    return err == ESP_OK;
}

bool EspNvs::WriteUint32(
    const std::string_view key,
    uint32_t value)
{
    Open(NVS_READWRITE);
    esp_err_t err = nvs_set_u32(_handle, key.data(), value);
    return err == ESP_OK;
}

bool EspNvs::ReadUint32(
    const std::string_view key,
    uint32_t& value)
{
    Open(NVS_READONLY);
    esp_err_t err = nvs_get_u32(_handle, key.data(), &value);
    return err == ESP_OK;
}

bool EspNvs::WriteBlob(
    const std::string_view key,
    const uint8_t* data,
    size_t length)
{
    Open(NVS_READWRITE);
    esp_err_t err = nvs_set_blob(_handle, key.data(), data, length);
    return err == ESP_OK;
}

bool EspNvs::ReadBlob(
    const std::string_view key,
    uint8_t* data,
    size_t& length)
{
    Open(NVS_READONLY);
    size_t blobLength = length;
    esp_err_t err = nvs_get_blob(_handle, key.data(), data, &blobLength);
    length = blobLength;
    return err == ESP_OK;
}

bool EspNvs::EraseKey(
    const std::string_view key)
{
    Open(NVS_READWRITE);
    esp_err_t err = nvs_erase_key(_handle, key.data());
    Assert::IsTrue(Types::ETaskId::System, err == ESP_OK, "Failed to erase NVS key");
    return err == ESP_OK;
}

bool EspNvs::EraseNamespace()
{
    Open(NVS_READWRITE);
    esp_err_t err = nvs_erase_all(_handle);
    Assert::IsTrue(Types::ETaskId::System, err == ESP_OK, "Failed to erase NVS namespace");
    return CommitAndClose();
}

void EspNvs::Close()
{
    Assert::IsTrue(Types::ETaskId::System, _handle != 0, "NVS not opened");
    nvs_close(_handle); 
    _handle = 0;
}

bool EspNvs::CommitAndClose()
{
    Assert::IsTrue(Types::ETaskId::System, _handle != 0, "NVS not opened");
    esp_err_t err = nvs_commit(_handle);
    if (err == ESP_OK)
    {
        Close();
    }
    return err == ESP_OK;
}

#endif // ESP_PLATFORM
