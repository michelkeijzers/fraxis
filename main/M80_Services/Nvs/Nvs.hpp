#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <string_view>

class Nvs
{
public:
    Nvs();
    virtual ~Nvs();

    virtual bool Initialize() = 0;
    virtual void SetPartition(
        const std::string_view partition);
    virtual void SetNamespace(
        const std::string_view namespaceName);

    virtual bool WriteString(
        const std::string_view key,
        const std::string_view value) = 0;
    virtual bool ReadString(
        const std::string_view key,
        std::string& value) = 0;
    virtual bool WriteUint8(
        const std::string_view key,
        uint8_t value) = 0;
    virtual bool ReadUint8(
        const std::string_view key,
        uint8_t& value) = 0;
    virtual bool WriteUint16(
        const std::string_view key,
        uint16_t value) = 0;
    virtual bool ReadUint16(
        const std::string_view key,
        uint16_t& value) = 0;
    virtual bool WriteUint32(
        const std::string_view key,
        uint32_t value) = 0;
    virtual bool ReadUint32(
        const std::string_view key,
        uint32_t& value) = 0;
    virtual bool WriteBlob(
        const std::string_view key,
        const uint8_t* data,
        size_t length) = 0;
    virtual bool ReadBlob(
        const std::string_view key,
        uint8_t* data,
        size_t& length) = 0;
    virtual bool EraseKey(
        const std::string_view key) = 0;
    virtual bool EraseNamespace() = 0;

    protected:
        const std::string_view GetPartition() const;
        const std::string_view GetNamespace() const;

    private:
        std::string _partition;
        std::string _namespaceName;
};
