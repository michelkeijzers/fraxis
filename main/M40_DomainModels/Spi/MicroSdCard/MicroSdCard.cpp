#include "MicroSdCard.hpp"
#include "../../../M50_DeviceModels/Spi/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../../../M90_Utilities/Assert/Assert.hpp"

MicroSdCard::MicroSdCard(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
: 
    DomainModel(assert, log),
    _isInitialized(false),
    _microSdCardDeviceModel(nullptr)
{
    // No functionality required
}

void MicroSdCard::SetDeviceModel(
    M50::IDeviceModel& deviceModel)
{
    _microSdCardDeviceModel = static_cast<M50::Spi::MicroSdCardDeviceModel*>(&deviceModel);
}

void MicroSdCard::Initialize()
{
    _isInitialized = true;
}

bool MicroSdCard::IsInitialized() const
{
    return _isInitialized;
}

M90::Dirty::Dirty& MicroSdCard::GetDirty()
{
    return _dirty;
}

bool MicroSdCard::OpenFile(
    std::string_view filePath)
{
    return GetMicroSdCardDeviceModel().OpenFile(filePath);
}

bool MicroSdCard::CloseFile()
{
    return GetMicroSdCardDeviceModel().CloseFile();
}

bool MicroSdCard::ReadFile(
    uint8_t* buffer,
    size_t length,
    size_t* bytesRead)
{
    return GetMicroSdCardDeviceModel().ReadFile(buffer, length, bytesRead);
}

bool MicroSdCard::WriteFile(
    const uint8_t* buffer,
    size_t length,
    size_t* bytesWritten)
{
    return GetMicroSdCardDeviceModel().WriteFile(buffer, length, bytesWritten);
}

bool MicroSdCard::SeekFile(
    size_t offset,
    uint8_t origin)
{
    return GetMicroSdCardDeviceModel().SeekFile(offset, origin);
}

size_t MicroSdCard::GetFileSize()
{
    return GetMicroSdCardDeviceModel().GetFileSize();
}

bool MicroSdCard::FileExists(
    std::string_view filePath)
{
    return GetMicroSdCardDeviceModel().FileExists(filePath);
}

bool MicroSdCard::DeleteFile(
    std::string_view filePath)
{
    return GetMicroSdCardDeviceModel().DeleteFile(filePath);
}

bool MicroSdCard::ListFiles(
    std::vector<std::string>& fileList)
{
    return GetMicroSdCardDeviceModel().ListFiles(fileList);
}

M50::Spi::MicroSdCardDeviceModel& MicroSdCard::GetMicroSdCardDeviceModel()
{
    return *_microSdCardDeviceModel;
}
