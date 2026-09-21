#pragma once

#include "../DeviceDriver.hpp"
#include <cstdint>
#include <cstddef>

class Spi;

class MicroSdDeviceDriver : public DeviceDriver
{
public:
    MicroSdDeviceDriver();
    ~MicroSdDeviceDriver() = default;

    Spi& GetSpi();
    void SetSpi(
        Spi& spi);
    void SetConfiguration(
        uint8_t port,
        uint8_t mosiPin,
        uint8_t misoPin,
        uint8_t sclkPin,
        uint8_t csPin,
        uint32_t frequency);
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
    void AssertValidPort(
        uint8_t port);

    uint8_t _port;
    uint8_t _mosiPin;
    uint8_t _misoPin;
    uint8_t _sclkPin;
    uint8_t _csPin;
    uint32_t _frequency;
    Spi* _spi;
};
