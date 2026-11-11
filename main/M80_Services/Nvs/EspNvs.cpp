#ifdef ESP_PLATFORM

#include "EspNvs.hpp"
#include "nvs_flash.h"
#include "nvs.h"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include <string.h>
#include <vector>

EspNvs::EspNvs()
:
    _handle(0)
{
    SetReadWriteMode(EReadWriteMode::ReadOnly);
}

esp_err_t EspNvs::FlashInit()
{
    return nvs_flash_init();
}

esp_err_t EspNvs::FlashErase()
{
    return nvs_flash_erase();
}

esp_err_t EspNvs::Open(
    EReadWriteMode mode)
{
    // Make reading possible with NVS_READWRITE to prevent unnecessary nvs_open_from_partition 
    // calls.
    if ((_handle == 0) || GoingFromReadOnlyToReadWrite(mode))
    {
        return nvs_open_from_partition(
            GetPartition().data(), 
            GetNamespace().data(), 
            ReadWriteModeToNvsReadWriteMode(GetReadWriteMode()), 
            &_handle);
    }
    return ESP_OK;
}

esp_err_t EspNvs::WriteStringWhileInReadWriteMode(
    std::string_view key,
    std::string_view value)
{
    return nvs_set_str(_handle, key.data(), value.data());
}

esp_err_t EspNvs::ReadStringWhileInReadOnlyMode(
    std::string_view key,
    std::string& value)
{
    size_t length = 0;
    return nvs_get_str(_handle, key.data(), value.data(), &length);
}

esp_err_t EspNvs::WriteUint8WhileInReadWriteMode(
    std::string_view key,
    uint8_t value)
{
    return nvs_set_u8(_handle, key.data(), value);
}

esp_err_t EspNvs::ReadUint8WhileInReadOnlyMode(
    std::string_view key,
    uint8_t& value)
{
    return nvs_get_u8(_handle, key.data(), &value);
}

esp_err_t EspNvs::WriteUint16WhileInReadWriteMode(
    std::string_view key,
    uint16_t value)
{
    return nvs_set_u16(_handle, key.data(), value);
}

esp_err_t EspNvs::ReadUint16WhileInReadOnlyMode(
    std::string_view key,
    uint16_t& value)
{
    return nvs_get_u16(_handle, key.data(), &value);
}

esp_err_t EspNvs::WriteUint32WhileInReadWriteMode(
    std::string_view key,
    uint32_t value)
{
    return nvs_set_u32(_handle, key.data(), value);
}

esp_err_t EspNvs::ReadUint32WhileInReadOnlyMode(
    std::string_view key,
    uint32_t& value)
{
    return nvs_get_u32(_handle, key.data(), &value);
}

esp_err_t EspNvs::WriteBlobWhileInReadWriteMode(
    std::string_view key,
    const uint8_t* data,
    size_t length)
{
    return nvs_set_blob(_handle, key.data(), data, length);
}

esp_err_t EspNvs::ReadBlobWhileInReadOnlyMode(
    std::string_view key,
    uint8_t* data,
    size_t& length)
{
    return nvs_get_blob(_handle, key.data(), data, &length);
}

esp_err_t EspNvs::EraseKey(
    std::string_view key)
{
    Open(EReadWriteMode::ReadWrite);
    return nvs_erase_key(_handle, key.data());
}

esp_err_t EspNvs::EraseNamespace()
{
    Open(EReadWriteMode::ReadWrite);
    esp_err_t err = nvs_erase_all(_handle);
    if (err == ESP_OK)
    {
        err = CommitAndClose();
    }
    return err;
}

esp_err_t EspNvs::Close()
{
    if (_handle == 0)
    {
        return ESP_FAIL;
    }

    nvs_close(_handle);
    _handle = 0;
    return ESP_OK;
}

esp_err_t EspNvs::CommitAndClose()
{
    if (_handle != 0)
    {
        return ESP_FAIL;
    }

    esp_err_t err = nvs_commit(_handle);
    if (err == ESP_OK)
    {
        err = Close();
    }
    return err;
}

nvs_open_mode_t EspNvs::ReadWriteModeToNvsReadWriteMode(
    EReadWriteMode mode)
{
    switch (mode)
    {
        case EReadWriteMode::ReadOnly:
            return NVS_READONLY;

        case EReadWriteMode::ReadWrite:
            return NVS_READWRITE;

        default:
            return NVS_READONLY;
    }
}
    
#endif // ESP_PLATFORM
