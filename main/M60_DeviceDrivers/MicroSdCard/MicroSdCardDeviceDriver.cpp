#include "MicroSdCardDeviceDriver.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../../M80_Services/Spi/Spi.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

MicroSdCardDeviceDriver::MicroSdCardDeviceDriver()
{
}

void MicroSdCardDeviceDriver::Initialize()
{
}

SpiDeviceDriver& MicroSdCardDeviceDriver::GetSpiDeviceDriver()
{
    return *_spiDeviceDriver;
}

void MicroSdCardDeviceDriver::SetSpiDeviceDriver(
    SpiDeviceDriver& spiDeviceDriver)
{
    _spiDeviceDriver = &spiDeviceDriver; 
}

bool MicroSdCardDeviceDriver::OpenFile(
    const std::string& filePath)
{
    //TODOMICROSD
    return true;
}

bool MicroSdCardDeviceDriver::CloseFile()
{
    //TODOMICROSD
    return true;
}

bool MicroSdCardDeviceDriver::ReadFile(
    uint8_t* buffer,
    size_t length,
    size_t* bytesRead)
{
    //TODOMICROSD
    if (bytesRead != nullptr)
    {
        *bytesRead = 0;
    }
    return false;
}

bool MicroSdCardDeviceDriver::WriteFile(
    const uint8_t* buffer,
    size_t length,
    size_t* bytesWritten)
{
    //TODOMICROSD
    if (bytesWritten != nullptr)
    {
        *bytesWritten = length;
    }
    return true;
}

bool MicroSdCardDeviceDriver::SeekFile(
    size_t offset,
    uint8_t origin)
{
    //TODOMICROSD
    return true;
}

size_t MicroSdCardDeviceDriver::GetFileSize()
{
    //TODOMICROSD
    return 0;
}

bool MicroSdCardDeviceDriver::FileExists(
    const std::string& filePath)
{
    //TODOMICROSD
    return false;
}

bool MicroSdCardDeviceDriver::DeleteFile(
    const std::string& filePath)
{
    //TODOMICROSD
    return false;
}

bool MicroSdCardDeviceDriver::ListFiles(
    std::vector<std::string>& fileList)
{
    //TODOMICROSD
    fileList.clear();
    return true;
}
