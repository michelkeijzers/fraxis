#include "WindowsNvs.hpp"

#include <cstring>
#include <filesystem>
#include <fstream>

bool WindowsNvs::Initialize()
{
    std::filesystem::create_directories(GetBasePath());
    return true;
}

bool WindowsNvs::WriteString(
    std::string_view key,
    std::string_view value)
{
    return WriteBlob(key, reinterpret_cast<const uint8_t*>(value.data()), value.size()); // NOSONAR
}

bool WindowsNvs::ReadString(
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

    file.read(value.data(),static_cast<std::streamsize>(size));
    return static_cast<bool>(file);
}

bool WindowsNvs::WriteUint8(
    std::string_view key,
    uint8_t value)
{
    return WriteBlob(key, &value, sizeof(value));
}

bool WindowsNvs::ReadUint8(
    std::string_view key,
    uint8_t& value)
{
    size_t length = sizeof(value);
    return ReadBlob(key, &value, length) && length == sizeof(value);
}

bool WindowsNvs::WriteUint16(
    std::string_view key,
    uint16_t value)
{
    return WriteBlob(key, reinterpret_cast<const uint8_t*>(&value), sizeof(value)); // NOSONAR
}

bool WindowsNvs::ReadUint16(
    std::string_view key,
    uint16_t& value)
{
    size_t length = sizeof(value);
    return ReadBlob(key, reinterpret_cast<uint8_t*>(&value), length) && // NOSONAR
        length == sizeof(value);
}

bool WindowsNvs::WriteUint32(
    std::string_view key,
    uint32_t value)
{
    return WriteBlob(key, reinterpret_cast<const uint8_t*>(&value), sizeof(value)); // NOSONAR
}

bool WindowsNvs::ReadUint32(
    std::string_view key,
    uint32_t& value)
{
    size_t length = sizeof(value);
    return ReadBlob(key, reinterpret_cast<uint8_t*>(&value), length) && // NOSONAR
        length == sizeof(value);
}

bool WindowsNvs::WriteBlob(
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

bool WindowsNvs::ReadBlob(
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
