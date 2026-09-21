#include "MicroSdDeviceModel.hpp"

MicroSdDeviceModel::MicroSdDeviceModel()
: _spiPort(0),
  _csPin(0),
  _isFileOpen(false)
{
}

void MicroSdDeviceModel::Initialize()
{
}

uint8_t MicroSdDeviceModel::GetSpiPort() const
{
    return _spiPort;
}

void MicroSdDeviceModel::SetSpiPort(
    uint8_t spiPort)
{
    _spiPort = spiPort;
}

uint8_t MicroSdDeviceModel::GetCsPin() const
{
    return _csPin;
}

void MicroSdDeviceModel::SetCsPin(
    uint8_t csPin)
{
    _csPin = csPin;
}

bool MicroSdDeviceModel::OpenFile(
    const std::string& filePath)
{
    _currentFilePath = filePath;
    _isFileOpen = true;
    return true;
}

bool MicroSdDeviceModel::CloseFile()
{
    _isFileOpen = false;
    _currentFilePath.clear();
    return true;
}

bool MicroSdDeviceModel::ReadFile(
    uint8_t* buffer,
    size_t length,
    size_t* bytesRead)
{
    if (bytesRead != nullptr)
    {
        *bytesRead = 0;
    }
    return false;
}

bool MicroSdDeviceModel::WriteFile(
    const uint8_t* buffer,
    size_t length,
    size_t* bytesWritten)
{
    if (bytesWritten != nullptr)
    {
        *bytesWritten = length;
    }
    return true;
}

bool MicroSdDeviceModel::SeekFile(
    size_t offset,
    uint8_t origin)
{
    return true;
}

size_t MicroSdDeviceModel::GetFileSize()
{
    return 0;
}

bool MicroSdDeviceModel::FileExists(
    const std::string& filePath)
{
    return false;
}

bool MicroSdDeviceModel::DeleteFile(
    const std::string& filePath)
{
    return false;
}

bool MicroSdDeviceModel::ListFiles(
    std::vector<std::string>& fileList)
{
    fileList.clear();
    return true;
}
