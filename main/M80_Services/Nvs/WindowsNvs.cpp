#include "WindowsNvs.hpp"
#include <filesystem>

WindowsNvs::WindowsNvs()
{
}

bool WindowsNvs::Initialize()
{
    return Load();
}

bool WindowsNvs::WriteString(
    std::string_view key,
    std::string_view value)
{
    Entry& entry = _entries[std::string(key)];

    entry.data.assign(
        value.begin(),
        value.end());

    return true;
}

bool WindowsNvs::ReadString(
    std::string_view key,
    std::string& value)
{
    value.clear();

    auto it = _entries.find(std::string(key));

    if (it == _entries.end())
    {
        return false;
    }

    value.assign(
        reinterpret_cast<const char*>(it->second.data.data()),
        it->second.data.size());

    return true;
}

bool WindowsNvs::WriteUint8(
    std::string_view key,
    uint8_t value)
{
    return WriteBlob(
        key,
        &value,
        sizeof(value));
}

bool WindowsNvs::ReadUint8(
    std::string_view key,
    uint8_t& value)
{
    size_t size = sizeof(value);

    return ReadBlob(
        key,
        &value,
        size);
}

bool WindowsNvs::WriteUint16(
    std::string_view key,
    uint16_t value)
{
    return WriteBlob(
        key,
        reinterpret_cast<const uint8_t*>(&value),
        sizeof(value));
}

bool WindowsNvs::ReadUint16(
    std::string_view key,
    uint16_t& value)
{
    size_t size = sizeof(value);

    return ReadBlob(
        key,
        reinterpret_cast<uint8_t*>(&value),
        size);
}

bool WindowsNvs::WriteUint32(
    std::string_view key,
    uint32_t value)
{
    return WriteBlob(
        key,
        reinterpret_cast<const uint8_t*>(&value),
        sizeof(value));
}

bool WindowsNvs::ReadUint32(
    std::string_view key,
    uint32_t& value)
{
    size_t size = sizeof(value);

    return ReadBlob(
        key,
        reinterpret_cast<uint8_t*>(&value),
        size);
}

bool WindowsNvs::WriteBlob(
    std::string_view key,
    const uint8_t* data,
    size_t length)
{
    Entry& entry = _entries[std::string(key)];

    entry.data.assign(
        data,
        data + length);

    return true;
}

bool WindowsNvs::ReadBlob(
    std::string_view key,
    uint8_t* data,
    size_t& length)
{
    auto it = _entries.find(std::string(key));

    if (it == _entries.end())
    {
        length = 0;
        return false;
    }

    const auto& source = it->second.data;

    if (length < source.size())
    {
        length = source.size();
        return false;
    }

    std::memcpy(
        data,
        source.data(),
        source.size());

    length = source.size();

    return true;
}

bool WindowsNvs::EraseKey(
    std::string_view key)
{
    _entries.erase(std::string(key));
    return true;
}

bool WindowsNvs::EraseNamespace()
{
    _entries.clear();
    return true;
}

bool WindowsNvs::Save()
{
    std::ofstream file(
        GetFilename(),
        std::ios::binary | std::ios::trunc);

    if (!file.is_open())
    {
        return false;
    }

    uint32_t count =
        static_cast<uint32_t>(_entries.size());

    file.write(
        reinterpret_cast<const char*>(&count),
        sizeof(count));

    for (const auto& [key, entry] : _entries)
    {
        uint32_t keyLength =
            static_cast<uint32_t>(key.size());

        uint32_t dataLength =
            static_cast<uint32_t>(entry.data.size());

        file.write(
            reinterpret_cast<const char*>(&keyLength),
            sizeof(keyLength));

        file.write(
            key.data(),
            keyLength);

        file.write(
            reinterpret_cast<const char*>(&dataLength),
            sizeof(dataLength));

        file.write(
            reinterpret_cast<const char*>(entry.data.data()),
            dataLength);
    }

    return true;
}

bool WindowsNvs::Load()
{
    _entries.clear();

    std::ifstream file(
        GetFilename(),
        std::ios::binary);

    if (!file.is_open())
    {
        return true;
    }

    uint32_t count = 0;

    file.read(
        reinterpret_cast<char*>(&count),
        sizeof(count));

    for (uint32_t index = 0; index < count; index++)
    {
        uint32_t keyLength = 0;
        uint32_t dataLength = 0;

        file.read(
            reinterpret_cast<char*>(&keyLength),
            sizeof(keyLength));

        std::string key(keyLength, '\0');

        file.read(
            key.data(),
            keyLength);

        file.read(
            reinterpret_cast<char*>(&dataLength),
            sizeof(dataLength));

        Entry entry;

        entry.data.resize(dataLength);

        file.read(
            reinterpret_cast<char*>(entry.data.data()),
            dataLength);

        _entries.emplace(
            std::move(key),
            std::move(entry));
    }

    return true;
}

std::string WindowsNvs::GetFilename() const
{
    std::string filename;

    filename.reserve(128);

    filename.append("Storage/");
    filename.append(GetPartition());
    filename.append("_");
    filename.append(GetNamespace());
    filename.append(".bin");

    return filename;
}