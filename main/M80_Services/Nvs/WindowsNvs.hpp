#pragma once

#include "Nvs.hpp"
#include <cstdint>
#include <cstddef>
#include <string>
#include <string_view>
#include <map>
#include <vector>
#include <fstream>

class WindowsNvs : public Nvs
{
public:
    WindowsNvs() = default;
    virtual ~WindowsNvs() = default;

    bool Initialize() override;

    bool WriteString(
        const std::string_view key,
        const std::string_view value) override;

    bool ReadString(
        const std::string_view key,
        std::string& value) override;

    bool WriteUint8(
        const std::string_view key,
        uint8_t value) override;

    bool ReadUint8(
        const std::string_view key,
        uint8_t& value) override;

    bool WriteUint16(
        const std::string_view key,
        uint16_t value) override;

    bool ReadUint16(
        const std::string_view key,
        uint16_t& value) override;

    bool WriteUint32(
        const std::string_view key,
        uint32_t value) override;

    bool ReadUint32(
        const std::string_view key,
        uint32_t& value) override;

    bool WriteBlob(
        const std::string_view key,
        const uint8_t* data,
        size_t length) override;

    bool ReadBlob(
        const std::string_view key,
        uint8_t* data,
        size_t& length) override;

    bool EraseKey(
        const std::string_view key) override;

    bool EraseNamespace() override;

private:
    struct Entry
    {
        std::vector<std::byte> data;
    };

    std::string GetFilename() const;

    
    template<typename T>
    static bool ReadValue(
        std::ifstream& file,
        T& value);

    static bool ReadBytes(
        std::ifstream& file,
        std::vector<std::byte>& data);

    bool Load();

    bool Save() const;

    std::map<std::string, Entry, std::less<>> _entries;
};