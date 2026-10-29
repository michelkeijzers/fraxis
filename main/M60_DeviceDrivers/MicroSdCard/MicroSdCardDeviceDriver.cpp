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

// Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
MicroSdCardDeviceDriver::~MicroSdCardDeviceDriver() = default;

void MicroSdCardDeviceDriver::Initialize()
{
    // NOSONAR TODO I2S
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
    std::string_view /* filePath */)
{
    // NOSONAR TODO SD
    return true;
}

bool MicroSdCardDeviceDriver::CloseFile() // NOSONAR S5817: const
{
    // NOSONAR TODO SD
    return true;
}

bool MicroSdCardDeviceDriver::ReadFile( // NOSONAR S5817: const
    uint8_t* /* buffer */,
    size_t /* length */,
    size_t* bytesRead)
{
    // NOSONAR TODO SD
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
    // NOSONAR TODO SD
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
    // NOSONAR TODO SD
    return true;
}

size_t MicroSdCardDeviceDriver::GetFileSize() const
{
    // NOSONAR TODO SD
    return 0;
}

bool MicroSdCardDeviceDriver::FileExists(
    std::string_view /* filePath */) const
{
    // NOSONAR TODO SD
    return false;
}

bool MicroSdCardDeviceDriver::DeleteFile( // NOSONAR S5817 const
    std::string_view /* filePath */)
{
    // NOSONAR TODO SD
    return false;
}

bool MicroSdCardDeviceDriver::ListFiles(// NOSONAR S5817 const
    std::vector<std::string>& fileList)
{
    // NOSONAR TODO SD
    fileList.clear();
    return true;
}
