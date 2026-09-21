#include "MicroSd.hpp"
#include "../../../../M10_Composition/Context/DeviceModelsContext.hpp"
#include "../../../../M50_DeviceModels/MicroSd/MicroSdDeviceModel.hpp"

MicroSd::MicroSd()
: _isInitialized(false),
  _microSdDeviceModel(nullptr)
{
}

void MicroSd::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _microSdDeviceModel = static_cast<MicroSdDeviceModel*>(&deviceModel);
}

void MicroSd::Initialize()
{
    _isInitialized = true;
}

bool MicroSd::IsInitialized() const
{
    return _isInitialized;
}

bool MicroSd::OpenFile(
    const std::string& filePath)
{
    return GetMicroSdDeviceModel().OpenFile(filePath);
}

bool MicroSd::CloseFile()
{
    return GetMicroSdDeviceModel().CloseFile();
}

bool MicroSd::ReadFile(
    uint8_t* buffer,
    size_t length,
    size_t* bytesRead)
{
    return GetMicroSdDeviceModel().ReadFile(buffer, length, bytesRead);
}

bool MicroSd::WriteFile(
    const uint8_t* buffer,
    size_t length,
    size_t* bytesWritten)
{
    return GetMicroSdDeviceModel().WriteFile(buffer, length, bytesWritten);
}

bool MicroSd::SeekFile(
    size_t offset,
    uint8_t origin)
{
    return GetMicroSdDeviceModel().SeekFile(offset, origin);
}

size_t MicroSd::GetFileSize()
{
    return GetMicroSdDeviceModel().GetFileSize();
}

bool MicroSd::FileExists(
    const std::string& filePath)
{
    return GetMicroSdDeviceModel().FileExists(filePath);
}

bool MicroSd::DeleteFile(
    const std::string& filePath)
{
    return GetMicroSdDeviceModel().DeleteFile(filePath);
}

bool MicroSd::ListFiles(
    std::vector<std::string>& fileList)
{
    return GetMicroSdDeviceModel().ListFiles(fileList);
}

MicroSdDeviceModel& MicroSd::GetMicroSdDeviceModel()
{
    return *_microSdDeviceModel;
}
