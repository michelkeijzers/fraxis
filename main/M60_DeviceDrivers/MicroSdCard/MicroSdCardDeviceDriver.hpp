#pragma once

#include "../Spi/SpiDeviceDriver.hpp"
#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

class Spi;

class MicroSdCardDeviceDriver : public DeviceDriver
{
public:
    MicroSdCardDeviceDriver();
    ~MicroSdCardDeviceDriver() = default;

    SpiDeviceDriver& GetSpiDeviceDriver();
    void SetSpiDeviceDriver(
        SpiDeviceDriver& spiDeviceDriver);
    void Initialize() override;

    bool OpenFile(
        const std::string& filePath);
    bool CloseFile();
    bool ReadFile(
        uint8_t* buffer,
        size_t length,
        size_t* bytesRead);
    bool WriteFile(
        const uint8_t* buffer,
        size_t length,
        size_t* bytesWritten);
    bool SeekFile(
        size_t offset,
        uint8_t origin);
    size_t GetFileSize();
    bool FileExists(
        const std::string& filePath);
    bool DeleteFile(
        const std::string& filePath);
    bool ListFiles(
        std::vector<std::string>& fileList);

private:
    SpiDeviceDriver* _spiDeviceDriver;
};
