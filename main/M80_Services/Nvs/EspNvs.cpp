#ifdef ESP_PLATFORM

#include "EspNvs.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include "nvs_flash.h"
#include "nvs.h"
#include <string.h>

EspNvs::EspNvs()
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
        Assert::IsTrue(Types::ETaskId::System, nvs_flash_erase() == ESP_OK, "Failed to erase NVS flash");
        err = nvs_flash_init();
    }
    Assert::IsTrue(Types::ETaskId::System, err == ESP_OK, "Failed to initialize NVS flash");
    return true;
}

esp_err_t EspNvs::Open(
    const std::string& partition,
    const std::string& namespaceName,
    nvs_open_mode_t mode,
    nvs_handle_t& handle)
{
    return nvs_open_from_partition(
        partition.c_str(),
        namespaceName.c_str(),
        mode,
        &handle);
}

bool EspNvs::WriteString(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    const std::string& value)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READWRITE, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    err = nvs_set_str(handle, key.c_str(), value.c_str());
    if (err != ESP_OK)
    {
        nvs_close(handle);
        return false;
    }

    err = nvs_commit(handle);
    nvs_close(handle);
    return err == ESP_OK;
}

bool EspNvs::ReadString(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    std::string& value)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READONLY, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    size_t length = 0;
    err = nvs_get_str(handle, key.c_str(), nullptr, &length);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND)
    {
        nvs_close(handle);
        return false;
    }

    if (length == 0)
    {
        value.clear();
        nvs_close(handle);
        return true;
    }

    char* buffer = new char[length];
    err = nvs_get_str(handle, key.c_str(), buffer, &length);
    if (err != ESP_OK)
    {
        delete[] buffer;
        nvs_close(handle);
        return false;
    }

    value = buffer;
    delete[] buffer;
    nvs_close(handle);
    return true;
}

bool EspNvs::WriteUint8(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint8_t value)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READWRITE, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    err = nvs_set_u8(handle, key.c_str(), value);
    if (err != ESP_OK)
    {
        nvs_close(handle);
        return false;
    }

    err = nvs_commit(handle);
    nvs_close(handle);
    return err == ESP_OK;
}

bool EspNvs::ReadUint8(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint8_t& value)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READONLY, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    err = nvs_get_u8(handle, key.c_str(), &value);
    nvs_close(handle);
    return err == ESP_OK || err == ESP_ERR_NVS_NOT_FOUND;
}

bool EspNvs::WriteUint16(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint16_t value)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READWRITE, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    err = nvs_set_u16(handle, key.c_str(), value);
    if (err != ESP_OK)
    {
        nvs_close(handle);
        return false;
    }

    err = nvs_commit(handle);
    nvs_close(handle);
    return err == ESP_OK;
}

bool EspNvs::ReadUint16(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint16_t& value)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READONLY, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    err = nvs_get_u16(handle, key.c_str(), &value);
    nvs_close(handle);
    return err == ESP_OK || err == ESP_ERR_NVS_NOT_FOUND;
}

bool EspNvs::WriteUint32(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint32_t value)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READWRITE, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    err = nvs_set_u32(handle, key.c_str(), value);
    if (err != ESP_OK)
    {
        nvs_close(handle);
        return false;
    }

    err = nvs_commit(handle);
    nvs_close(handle);
    return err == ESP_OK;
}

bool EspNvs::ReadUint32(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint32_t& value)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READONLY, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    err = nvs_get_u32(handle, key.c_str(), &value);
    nvs_close(handle);
    return err == ESP_OK || err == ESP_ERR_NVS_NOT_FOUND;
}

bool EspNvs::WriteBlob(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    const uint8_t* data,
    size_t length)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READWRITE, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    err = nvs_set_blob(handle, key.c_str(), data, length);
    if (err != ESP_OK)
    {
        nvs_close(handle);
        return false;
    }

    err = nvs_commit(handle);
    nvs_close(handle);
    return err == ESP_OK;
}

bool EspNvs::ReadBlob(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint8_t* data,
    size_t& length)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READONLY, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    size_t blobLength = length;
    err = nvs_get_blob(handle, key.c_str(), data, &blobLength);
    if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND)
    {
        nvs_close(handle);
        return false;
    }

    length = blobLength;
    nvs_close(handle);
    return true;
}

bool EspNvs::EraseKey(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key)
{
    nvs_handle_t handle;
    esp_err_t err = Open(partition, namespaceName, NVS_READWRITE, handle);
    if (err != ESP_OK)
    {
        return false;
    }

    err = nvs_erase_key(handle, key.c_str());
    if (err != ESP_OK)
    {
        nvs_close(handle);
        return false;
    }

    err = nvs_commit(handle);
    nvs_close(handle);
    return err == ESP_OK;
}


bool EspNvs::EraseNamespace(
    const std::string& partition,
    const std::string& namespaceName)
{
    nvs_handle_t handle;

    esp_err_t err = nvs_open_from_partition(partition.c_str(), namespaceName.c_str(), NVS_READWRITE, &handle);
    if (err != ESP_OK)
    {
        return false;
    }

    err = nvs_erase_all(handle);
    if (err == ESP_OK)
    {
        err = nvs_commit(handle);
    }

    nvs_close(handle);
    return (err == ESP_OK);
}

#endif // ESP_PLATFORM
