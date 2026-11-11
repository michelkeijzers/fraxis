#include "Nvs.hpp"
#if ESP_PLATFORM
#include "nvs_flash.h"
#endif

Nvs::Nvs()
    :
    _readWriteMode(EReadWriteMode::ReadOnly)
{
}

esp_err_t Nvs::Initialize()
{
    bool needsFlashErase = false;
    esp_err_t err = FlashInit(needsFlashErase);
    if (err == ESP_OK && needsFlashErase)
    {
        err = FlashErase();
    }
    return err;
}

void Nvs::SetPartition(
    std::string_view partition)
{
    _partition = partition;
}

std::string_view Nvs::GetPartition() const
{
    return _partition;
}

void Nvs::SetNamespace(
    std::string_view namespaceName)
{
    _namespaceName = namespaceName;
}

std::string_view Nvs::GetNamespace() const
{
    return _namespaceName;
}

esp_err_t Nvs::FlashInit(
    bool& needsFlashErase)
{
    esp_err_t err = FlashInit();
    needsFlashErase = (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND);
    return err;
}

Nvs::EReadWriteMode Nvs::GetReadWriteMode() const
{
    return _readWriteMode;
}
    
void Nvs::SetReadWriteMode(
    EReadWriteMode readWriteMode)
{
    _readWriteMode = readWriteMode;
}

bool Nvs::GoingFromReadOnlyToReadWrite(
    EReadWriteMode mode) const
{
    return
        ((GetReadWriteMode() == EReadWriteMode::ReadOnly) &&
            (mode == EReadWriteMode::ReadWrite));
}

esp_err_t Nvs::ReadString(
    std::string_view key,
    std::string& value)
{
    Open(EReadWriteMode::ReadOnly);
    return ReadStringWhileInReadOnlyMode(key, value);
}

esp_err_t Nvs::WriteString(
    std::string_view key,
    std::string_view value)
{
    Open(EReadWriteMode::ReadWrite);
    return WriteStringWhileInReadWriteMode(key, value);
}

esp_err_t Nvs::ReadUint8(
    std::string_view key,
    uint8_t& value)
{
    Open(EReadWriteMode::ReadOnly);
    return ReadUint8WhileInReadOnlyMode(key, value);
}

esp_err_t Nvs::WriteUint8(
    std::string_view key,
    uint8_t value)
{
    Open(EReadWriteMode::ReadWrite);
    return WriteUint8WhileInReadWriteMode(key, value);
}

esp_err_t Nvs::ReadUint16(
    std::string_view key,
    uint16_t& value)
{
    Open(EReadWriteMode::ReadOnly);
    return ReadUint16WhileInReadOnlyMode(key, value);
}

esp_err_t Nvs::WriteUint16(
    std::string_view key,
    uint16_t value)
{
    Open(EReadWriteMode::ReadWrite);
    return WriteUint16WhileInReadWriteMode(key, value);
}

esp_err_t Nvs::ReadUint32(
    std::string_view key,
    uint32_t& value)
{
    Open(EReadWriteMode::ReadOnly);
    return ReadUint32WhileInReadOnlyMode(key, value);
}

esp_err_t Nvs::WriteUint32(
    std::string_view key,
    uint32_t value)
{
    Open(EReadWriteMode::ReadWrite);
    return WriteUint32WhileInReadWriteMode(key, value);
}

esp_err_t Nvs::ReadBlob(
    std::string_view key,
    uint8_t* data,
    size_t& length)
{
    Open(EReadWriteMode::ReadOnly);
    return ReadBlobWhileInReadOnlyMode(key, data, length);
}

esp_err_t Nvs::WriteBlob(
    std::string_view key,
    const uint8_t* data,
    size_t length)
{
    Open(EReadWriteMode::ReadWrite);
    return WriteBlobWhileInReadWriteMode(key, data, length);
}
