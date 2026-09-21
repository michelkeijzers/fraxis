#include "MicroSdDeviceDriver.hpp"
#include "../../M80_Services/Spi/Spi.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"

MicroSdDeviceDriver::MicroSdDeviceDriver()
: _port(0),
  _mosiPin(0),
  _misoPin(0),
  _sclkPin(0),
  _csPin(0),
  _frequency(0),
  _spi(nullptr)
{
}

Spi& MicroSdDeviceDriver::GetSpi()
{
    Assert::IsNotNull(_spi, "Spi not set");
    return *_spi;
}

void MicroSdDeviceDriver::SetSpi(
    Spi& spi)
{
    _spi = &spi;
}

void MicroSdDeviceDriver::SetConfiguration(
    uint8_t port,
    uint8_t mosiPin,
    uint8_t misoPin,
    uint8_t sclkPin,
    uint8_t csPin,
    uint32_t frequency)
{
    AssertValidPort(port);

    _port = port;
    _mosiPin = mosiPin;
    _misoPin = misoPin;
    _sclkPin = sclkPin;
    _csPin = csPin;
    _frequency = frequency;

    GetSpi().ParamConfig(port, mosiPin, misoPin, sclkPin, csPin, frequency);
    GetSpi().DriverInstall(port);
}

void MicroSdDeviceDriver::Initialize()
{
}

void MicroSdDeviceDriver::AssertValidPort(
    uint8_t port)
{
    if (!GetSpi().IsValidPort(port))
    {
        Assert::IsTrue(false, "Invalid SPI port");
    }
}

bool MicroSdDeviceDriver::OpenFile(
    const std::string& filePath)
{
    return true;
}

bool MicroSdDeviceDriver::CloseFile()
{
    return true;
}

bool MicroSdDeviceDriver::ReadFile(
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

bool MicroSdDeviceDriver::WriteFile(
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

bool MicroSdDeviceDriver::SeekFile(
    size_t offset,
    uint8_t origin)
{
    return true;
}

size_t MicroSdDeviceDriver::GetFileSize()
{
    return 0;
}

bool MicroSdDeviceDriver::FileExists(
    const std::string& filePath)
{
    return false;
}

bool MicroSdDeviceDriver::DeleteFile(
    const std::string& filePath)
{
    return false;
}

bool MicroSdDeviceDriver::ListFiles(
    std::vector<std::string>& fileList)
{
    fileList.clear();
    return true;
}
