#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <string_view>

class Nvs
{
public:
    Nvs();

    Nvs(const Nvs&) = delete;
    Nvs& operator=(const Nvs&) = delete;
    Nvs(Nvs&&) = delete;
    Nvs& operator=(Nvs&&) = delete;

    virtual ~Nvs();

    virtual bool Initialize() = 0;
    virtual void SetPartition(
        std::string_view partition);
    virtual void SetNamespace(
        std::string_view namespaceName);

    virtual bool WriteString(
        std::string_view key,
        std::string_view value) = 0;
    virtual bool ReadString(
        std::string_view key,
        std::string& value) = 0;
    virtual bool WriteUint8(
        std::string_view key,
        uint8_t value) = 0;
    virtual bool ReadUint8(
        std::string_view key,
        uint8_t& value) = 0;
    virtual bool WriteUint16(
        std::string_view key,
        uint16_t value) = 0;
    virtual bool ReadUint16(
        std::string_view key,
        uint16_t& value) = 0;
    virtual bool WriteUint32(
        std::string_view key,
        uint32_t value) = 0;
    virtual bool ReadUint32(
        std::string_view key,
        uint32_t& value) = 0;
    virtual bool WriteBlob(
        std::string_view key,
        const uint8_t* data,
        size_t length) = 0;
    virtual bool ReadBlob(
        std::string_view key,
        uint8_t* data,
        size_t& length) = 0;
    
    virtual bool EraseKey(
        std::string_view key) = 0;
    virtual bool EraseNamespace() = 0;

    virtual void Close() = 0;
/// <summary>
    /// Only needed when writing.
    /// </summary>
    virtual bool CommitAndClose() = 0;
    
    protected:
        [[nodiscard]] std::string_view GetPartition() const;
        [[nodiscard]] std::string_view GetNamespace() const;

    private:
        std::string _partition;
        std::string _namespaceName;
};
