#include "MicroSdCardDeviceModel.hpp"

MicroSdCardDeviceModel::MicroSdCardDeviceModel()
: 
    _spiPort(0),
    _csPin(0),
    _isFileOpen(false)
{
}

void MicroSdCardDeviceModel::Initialize()
{
}

uint8_t MicroSdCardDeviceModel::GetSpiPort() const
{
    return _spiPort;
}

void MicroSdCardDeviceModel::SetSpiPort(
    uint8_t spiPort)
{
    _spiPort = spiPort;
}

uint8_t MicroSdCardDeviceModel::GetCsPin() const
{
    return _csPin;
}

void MicroSdCardDeviceModel::SetCsPin(
    uint8_t csPin)
{
    _csPin = csPin;
}

bool MicroSdCardDeviceModel::OpenFile(
    const std::string& filePath)
{
    _currentFilePath = filePath;
    _isFileOpen = true;
    return true;
}

bool MicroSdCardDeviceModel::CloseFile()
{
    _isFileOpen = false;
    _currentFilePath.clear();
    return true;
}

bool MicroSdCardDeviceModel::ReadFile(
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

bool MicroSdCardDeviceModel::WriteFile(
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

bool MicroSdCardDeviceModel::SeekFile(
    size_t offset,
    uint8_t origin)
{
    return true;
}

size_t MicroSdCardDeviceModel::GetFileSize()
{
    return 0;
}

bool MicroSdCardDeviceModel::FileExists(
    const std::string& filePath)
{
    return false;
}

bool MicroSdCardDeviceModel::DeleteFile(
    const std::string& filePath)
{
    return false;
}

bool MicroSdCardDeviceModel::ListFiles(
    std::vector<std::string>& fileList)
{
    fileList.clear();
    return true;
}
