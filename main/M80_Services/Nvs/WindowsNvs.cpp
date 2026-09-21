#include "WindowsNvs.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include <string>

WindowsNvs::WindowsNvs()
{
}

bool WindowsNvs::Initialize()
{
    return true;
}

bool WindowsNvs::WriteString(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    const std::string& value)
{
    return true;
}

bool WindowsNvs::ReadString(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    std::string& value)
{
    value.clear();
    return true;
}

bool WindowsNvs::WriteUint8(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint8_t value)
{
    return true;
}

bool WindowsNvs::ReadUint8(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint8_t& value)
{
    value = 0;
    return true;
}

bool WindowsNvs::WriteUint16(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint16_t value)
{
    return true;
}

bool WindowsNvs::ReadUint16(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint16_t& value)
{
    value = 0;
    return true;
}

bool WindowsNvs::WriteUint32(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint32_t value)
{
    return true;
}

bool WindowsNvs::ReadUint32(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint32_t& value)
{
    value = 0;
    return true;
}

bool WindowsNvs::WriteBlob(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    const uint8_t* data,
    size_t length)
{
    return true;
}

bool WindowsNvs::ReadBlob(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key,
    uint8_t* data,
    size_t& length)
{
    length = 0;
    return true;
}

bool WindowsNvs::EraseKey(
    const std::string& partition,
    const std::string& namespaceName,
    const std::string& key)
{
    return true;
}

bool WindowsNvs::EraseNamespace(
    const std::string& partition,
    const std::string& namespaceName)
{
    return true;
}
