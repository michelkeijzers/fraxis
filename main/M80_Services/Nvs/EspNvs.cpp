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
    _handle(0)
{
    SetReadWriteMode(EReadWriteMode::ReadOnly);
}

bool EspNvs::FlashInit(
    bool& needsFlashErase)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        needsFlashErase = true;
        return true;
    }

    return err == ESP_OK;
}

bool EspNvs::FlashErase()
{
    return nvs_flash_erase() == ESP_OK;
}

bool EspNvs::Open(
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
            &_handle) == ESP_OK;
    }
    return true;
}

bool EspNvs::WriteStringWhileInReadWriteMode(
    std::string_view key,
    std::string_view value)
{
    esp_err_t err = nvs_set_str(_handle, key.data(), value.data());
    return err == ESP_OK;
}

bool EspNvs::ReadStringWhileInReadOnlyMode(
    std::string_view key,
    std::string& value)
{
    size_t length = 0;
    esp_err_t err = nvs_get_str(_handle, key.data(), value.data(), &length);
    return err == ESP_OK;
}

bool EspNvs::WriteUint8WhileInReadWriteMode(
    std::string_view key,
    uint8_t value)
{
    esp_err_t err = nvs_set_u8(_handle, key.data(), value);
    return err == ESP_OK;
}

bool EspNvs::ReadUint8WhileInReadOnlyMode(
    std::string_view key,
    uint8_t& value)
{
    esp_err_t err = nvs_get_u8(_handle, key.data(), &value);
    return err == ESP_OK;
}

bool EspNvs::WriteUint16WhileInReadWriteMode(
    std::string_view key,
    uint16_t value)
{
    esp_err_t err = nvs_set_u16(_handle, key.data(), value);
    return err == ESP_OK;
}

bool EspNvs::ReadUint16WhileInReadOnlyMode(
    std::string_view key,
    uint16_t& value)
{
    esp_err_t err = nvs_get_u16(_handle, key.data(), &value);
    return err == ESP_OK;
}

bool EspNvs::WriteUint32WhileInReadWriteMode(
    std::string_view key,
    uint32_t value)
{
    esp_err_t err = nvs_set_u32(_handle, key.data(), value);
    return err == ESP_OK;
}

bool EspNvs::ReadUint32WhileInReadOnlyMode(
    std::string_view key,
    uint32_t& value)
{
    esp_err_t err = nvs_get_u32(_handle, key.data(), &value);
    return err == ESP_OK;
}

bool EspNvs::WriteBlobWhileInReadWriteMode(
    std::string_view key,
    const uint8_t* data,
    size_t length)
{
    esp_err_t err = nvs_set_blob(_handle, key.data(), data, length);
    return err == ESP_OK;
}

bool EspNvs::ReadBlobWhileInReadOnlyMode(
    std::string_view key,
    uint8_t* data,
    size_t& length)
{
    size_t blobLength = length;
    esp_err_t err = nvs_get_blob(_handle, key.data(), data, &blobLength);
    length = blobLength;
    return err == ESP_OK;
}

bool EspNvs::EraseKey(
    std::string_view key)
{
    Open(EReadWriteMode::ReadWrite);
    esp_err_t err = nvs_erase_key(_handle, key.data());
    Assert::IsTrue(Types::ETaskId::System, err == ESP_OK, "Failed to erase NVS key");
    return err == ESP_OK;
}

bool EspNvs::EraseNamespace()
{
    Open(EReadWriteMode::ReadWrite);
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
            Assert::Fail(Types::ETaskId::System, "Invalid NVS read/write mode");
            return NVS_READONLY;
    }
}
    
#endif // ESP_PLATFORM
