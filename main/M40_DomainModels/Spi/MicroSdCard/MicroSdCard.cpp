#include "MicroSdCard.hpp"
#include "../../../M10_Composition/Context/DeviceModelsContext.hpp"
#include "../../../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../../../M90_Utilities/Assert/Assert.hpp"

MicroSdCard::MicroSdCard()
: 
    _isInitialized(false),
    _microSdCardDeviceModel(nullptr)
{
}

void MicroSdCard::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _microSdCardDeviceModel = static_cast<MicroSdCardDeviceModel*>(&deviceModel);
}

void MicroSdCard::Initialize()
{
    _isInitialized = true;
}

bool MicroSdCard::IsInitialized() const
{
    return _isInitialized;
}

Dirty& MicroSdCard::GetDirty() 
{
    return _dirty;
}

bool MicroSdCard::OpenFile(
    const std::string& filePath)
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
    const std::string& filePath)
{
    return GetMicroSdCardDeviceModel().FileExists(filePath);
}

bool MicroSdCard::DeleteFile(
    const std::string& filePath)
{
    return GetMicroSdCardDeviceModel().DeleteFile(filePath);
}

bool MicroSdCard::ListFiles(
    std::vector<std::string>& fileList)
{
    return GetMicroSdCardDeviceModel().ListFiles(fileList);
}

MicroSdCardDeviceModel& MicroSdCard::GetMicroSdCardDeviceModel()
{
    return *_microSdCardDeviceModel;
}
