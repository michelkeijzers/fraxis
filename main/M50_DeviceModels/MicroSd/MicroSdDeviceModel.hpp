#pragma once

#include "../../M60_DeviceDrivers/MicroSd/MicroSdDeviceDriver.hpp"
#include "../DeviceModel.hpp"
#include <cstdint>
#include <string>
#include <vector>

class MicroSdDeviceModel : public DeviceModel
{
public:
    MicroSdDeviceModel();
    ~MicroSdDeviceModel() = default;

    void Initialize() override;

    uint8_t GetSpiPort() const;
    void SetSpiPort(
        uint8_t spiPort);
    uint8_t GetCsPin() const;
    void SetCsPin(
        uint8_t csPin);

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
    uint8_t _spiPort;
    uint8_t _csPin;
    std::string _currentFilePath;
    bool _isFileOpen;
};
