#include "MicroSdCardDeviceDriver.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../../M80_Services/Spi/Spi.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

MicroSdCardDeviceDriver::MicroSdCardDeviceDriver()
:
    _spiDeviceDriver(nullptr)
{
}

void MicroSdCardDeviceDriver::Initialize()
{
    //TODO I2S
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

bool MicroSdCardDeviceDriver::OpenFile( // NOSONAR S5817: const
    const std::string_view /* filePath */)
{
    //TODOMICROSD
    return true;
}

bool MicroSdCardDeviceDriver::CloseFile() // NOSONAR S5817: const
{
    //TODOMICROSD
    return true;
}

bool MicroSdCardDeviceDriver::ReadFile( // NOSONAR S5817: const
    uint8_t* /* buffer */,
    size_t /* length */,
    size_t* bytesRead)
{
    //TODOMICROSD
    if (bytesRead != nullptr)
    {
        *bytesRead = 0;
    }
    return false;
}

bool MicroSdCardDeviceDriver::WriteFile( // NOSONAR const TODO
    const uint8_t* /* buffer */,
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

bool MicroSdCardDeviceDriver::SeekFile( // NOSONAR const TODO
    size_t /* offset */,
    uint8_t /* origin */)
{
    //TODOMICROSD
    return true;
}

size_t MicroSdCardDeviceDriver::GetFileSize() const
{
    //TODOMICROSD
    return 0;
}

bool MicroSdCardDeviceDriver::FileExists(
    const std::string_view /* filePath */) const
{
    //TODOMICROSD
    return false;
}

bool MicroSdCardDeviceDriver::DeleteFile( // NOSONAR S5817 const
    const std::string_view /* filePath */)
{
    //TODOMICROSD
    return false;
}

bool MicroSdCardDeviceDriver::ListFiles(// NOSONAR S5817 const
    std::vector<std::string>& fileList)
{
    //TODOMICROSD
    fileList.clear();
    return true;
}
