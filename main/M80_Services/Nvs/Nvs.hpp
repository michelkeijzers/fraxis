#pragma once

#include <cstdint>
#include <cstddef>
#include <string>

class Nvs
{
public:
    Nvs();
    virtual ~Nvs();

    virtual bool Initialize() = 0;
    virtual bool WriteString(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        const std::string& value) = 0;
    virtual bool ReadString(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        std::string& value) = 0;
    virtual bool WriteUint8(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint8_t value) = 0;
    virtual bool ReadUint8(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint8_t& value) = 0;
    virtual bool WriteUint16(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint16_t value) = 0;
    virtual bool ReadUint16(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint16_t& value) = 0;
    virtual bool WriteUint32(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint32_t value) = 0;
    virtual bool ReadUint32(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint32_t& value) = 0;
    virtual bool WriteBlob(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        const uint8_t* data,
        size_t length) = 0;
    virtual bool ReadBlob(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key,
        uint8_t* data,
        size_t& length) = 0;
    virtual bool EraseKey(
        const std::string& partition,
        const std::string& namespaceName,
        const std::string& key) = 0;
    virtual bool EraseNamespace(
        const std::string& partition,
        const std::string& namespaceName) = 0;
};
