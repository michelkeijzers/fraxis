#include "WindowsNvs.hpp"

#include <cstring>
#include <filesystem>
#include <fstream>

bool WindowsNvs::FlashInit(
    bool&)
{
    std::filesystem::create_directories(GetBasePath());
    return true;
}

bool WindowsNvs::FlashErase()
{
    // No action needed.
    return true;
}

bool WindowsNvs::Open(
    EReadWriteMode)
{
    // No action needed.
    return true;
}   

bool WindowsNvs::ReadStringWhileInReadOnlyMode(
    std::string_view key,
    std::string& value)
{
    value.clear();

    auto path = GetKeyPath(key);
    if (!std::filesystem::exists(path))
    {
        return false;
    }

    const auto size = static_cast<size_t>(std::filesystem::file_size(path));
    value.resize(size);
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.read(value.data(), static_cast<std::streamsize>(size));
    return static_cast<bool>(file);
}

bool WindowsNvs::WriteStringWhileInReadWriteMode(
    std::string_view key,
    std::string_view value)
{
    return WriteBlob(key, reinterpret_cast<const uint8_t*>(value.data()), value.size()); // NOSONAR
}

bool WindowsNvs::ReadUint8WhileInReadOnlyMode(
    std::string_view key,
    uint8_t& value)
{
    size_t length = sizeof(value);
    return ReadBlob(key, &value, length) && length == sizeof(value);
}

bool WindowsNvs::WriteUint8WhileInReadWriteMode(
    std::string_view key,
    uint8_t value)
{
    return WriteBlob(key, &value, sizeof(value));
}

bool WindowsNvs::ReadUint16WhileInReadOnlyMode(
    std::string_view key,
    uint16_t& value)
{
    size_t length = sizeof(value);
    return ReadBlob(key, reinterpret_cast<uint8_t*>(&value), length) && // NOSONAR
        length == sizeof(value);
}

bool WindowsNvs::WriteUint16WhileInReadWriteMode(
    std::string_view key,
    uint16_t value)
{
    return WriteBlob(key, reinterpret_cast<const uint8_t*>(&value), sizeof(value)); // NOSONAR
}

bool WindowsNvs::ReadUint32WhileInReadOnlyMode(
    std::string_view key,
    uint32_t& value)
{
    size_t length = sizeof(value);
    return ReadBlob(key, reinterpret_cast<uint8_t*>(&value), length) && // NOSONAR
        length == sizeof(value);
}

bool WindowsNvs::WriteUint32WhileInReadWriteMode(
    std::string_view key,
    uint32_t value)
{
    return WriteBlob(key, reinterpret_cast<const uint8_t*>(&value), sizeof(value)); // NOSONAR
}

bool WindowsNvs::ReadBlobWhileInReadOnlyMode(
    std::string_view key,
    uint8_t* data,
    size_t& length)
{
    auto path = GetKeyPath(key);
    if (!std::filesystem::exists(path))
    {
        length = 0;
        return false;
    }

    const auto fileSize = static_cast<size_t>(std::filesystem::file_size(path));
    if (length < fileSize)
    {
        length = fileSize;
        return false;
    }

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    file.read(reinterpret_cast<char*>(data), static_cast<std::streamsize>(fileSize)); // NOSONAR

    if (!file)
    {
        return false;
    }

    length = fileSize;
    return true;
}

bool WindowsNvs::WriteBlobWhileInReadWriteMode(
    std::string_view key,
    const uint8_t* data,
    size_t length)
{
    std::filesystem::create_directories(GetBasePath());
    std::ofstream file(GetKeyPath(key), std::ios::binary | std::ios::trunc);
    if (!file.is_open())
    {
        return false;
    }

    file.write(
        reinterpret_cast<const char*>(data),
        static_cast<std::streamsize>(length)); // NOSONAR
    return static_cast<bool>(file);
}

bool WindowsNvs::EraseKey(
    std::string_view key)
{
    return std::filesystem::remove(GetKeyPath(key));
}

bool WindowsNvs::EraseNamespace()
{
    std::error_code ec;

    std::filesystem::remove_all(GetBasePath(),ec);
    return !ec;
}

void WindowsNvs::Close()
{
    // No action needed.
}

bool WindowsNvs::CommitAndClose()
{
    return true;
}

std::filesystem::path WindowsNvs::GetBasePath() const
{
    return std::filesystem::path("Storage") / 
        std::string(GetPartition()) / std::string(GetNamespace());
}

std::filesystem::path WindowsNvs::GetKeyPath(
    std::string_view key) const
{
    return GetBasePath() / std::string(key);
}
