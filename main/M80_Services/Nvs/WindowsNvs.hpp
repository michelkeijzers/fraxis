#pragma once

#include "Nvs.hpp"

#include <cstdint>
#include <cstddef>
#include <filesystem>
#include <string>
#include <string_view>

class WindowsNvs : public Nvs
{
public:
    WindowsNvs() = default;
    virtual ~WindowsNvs() = default;

    bool Initialize() override;

    bool WriteString(
        std::string_view key,
        std::string_view value) override;

    bool ReadString(
        std::string_view key,
        std::string& value) override;

    bool WriteUint8(
        std::string_view key,
        uint8_t value) override;

    bool ReadUint8(
        std::string_view key,
        uint8_t& value) override;

    bool WriteUint16(
        std::string_view key,
        uint16_t value) override;

    bool ReadUint16(
        std::string_view key,
        uint16_t& value) override;

    bool WriteUint32(
        std::string_view key,
        uint32_t value) override;

    bool ReadUint32(
        std::string_view key,
        uint32_t& value) override;

    bool WriteBlob(
        std::string_view key,
        const uint8_t* data,
        size_t length) override;

    bool ReadBlob(
        std::string_view key,
        uint8_t* data,
        size_t& length) override;

    bool EraseKey(
        std::string_view key) override;

    bool EraseNamespace() override;

    void Close() override;
    bool CommitAndClose() override;

private:
    std::filesystem::path GetBasePath() const;
    std::filesystem::path GetKeyPath(
        std::string_view key) const;
};
