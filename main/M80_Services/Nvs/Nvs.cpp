#include "Nvs.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
Nvs::Nvs()
    :
    _readWriteMode(EReadWriteMode::ReadOnly)
{
}

bool Nvs::Initialize()
{
    bool needsFlashErase = false;
    Assert::IsTrue(
        Types::ETaskId::System, 
        FlashInit(needsFlashErase), 
        "Failed to initialize NVS flash");

    if (needsFlashErase)
    {
        Assert::IsTrue(Types::ETaskId::System, FlashErase(), "Failed to erase NVS flash");
    }
    return true;
}

void Nvs::SetPartition(
    std::string_view partition)
{
    _partition = partition;
}

std::string_view Nvs::GetPartition() const
{
    return _partition;
}

void Nvs::SetNamespace(
    std::string_view namespaceName)
{
    _namespaceName = namespaceName;
}

std::string_view Nvs::GetNamespace() const
{
    return _namespaceName;
}

Nvs::EReadWriteMode Nvs::GetReadWriteMode() const
{
    return _readWriteMode;
}
    
void Nvs::SetReadWriteMode(
    EReadWriteMode readWriteMode)
{
    _readWriteMode = readWriteMode;
}

bool Nvs::GoingFromReadOnlyToReadWrite(
    EReadWriteMode mode) const
{
    return 
        ((GetReadWriteMode() == EReadWriteMode::ReadOnly) && 
         (mode == EReadWriteMode::ReadWrite));
}

bool Nvs::ReadString(
    std::string_view key,
    std::string& value)
{
    Open(EReadWriteMode::ReadOnly);
    return ReadStringWhileInReadOnlyMode(key, value);
}

bool Nvs::WriteString(
    std::string_view key,
    std::string_view value)
{
    Open(EReadWriteMode::ReadWrite);
    return WriteStringWhileInReadWriteMode(key, value);
}

bool Nvs::ReadUint8(
    std::string_view key,
    uint8_t& value)
{
    Open(EReadWriteMode::ReadOnly);
    return ReadUint8WhileInReadOnlyMode(key, value);
}

bool Nvs::WriteUint8(
    std::string_view key,
    uint8_t value)
{
    Open(EReadWriteMode::ReadWrite);
    return WriteUint8WhileInReadWriteMode(key, value);
}

bool Nvs::ReadUint16(
    std::string_view key,
    uint16_t& value)
{
    Open(EReadWriteMode::ReadOnly);
    return ReadUint16WhileInReadOnlyMode(key, value);
}

bool Nvs::WriteUint16(
    std::string_view key,
    uint16_t value)
{
    Open(EReadWriteMode::ReadWrite);
    return WriteUint16WhileInReadWriteMode(key, value);
}

bool Nvs::ReadUint32(
    std::string_view key,
    uint32_t& value)
{
    Open(EReadWriteMode::ReadOnly);
    return ReadUint32WhileInReadOnlyMode(key, value);
}

bool Nvs::WriteUint32(
    std::string_view key,
    uint32_t value)
{
    Open(EReadWriteMode::ReadWrite);
    return WriteUint32WhileInReadWriteMode(key, value);
}

bool Nvs::ReadBlob(
    std::string_view key,
    uint8_t* data,
    size_t& length)
{
    Open(EReadWriteMode::ReadOnly);
    return ReadBlobWhileInReadOnlyMode(key, data, length);
}

bool Nvs::WriteBlob(
    std::string_view key,
    const uint8_t* data,
    size_t length)
{
    Open(EReadWriteMode::ReadWrite);
    return WriteBlobWhileInReadWriteMode(key, data, length);
}
