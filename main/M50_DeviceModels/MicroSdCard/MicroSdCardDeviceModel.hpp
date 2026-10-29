#pragma once

#include "../../M60_DeviceDrivers/MicroSdCard/MicroSdCardDeviceDriver.hpp"
#include "../DeviceModel.hpp"
#include <cstdint>
#include <string>
#include <vector>

class MicroSdCardDeviceModel : public DeviceModel
{
public:
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    MicroSdCardDeviceModel();

    MicroSdCardDeviceModel(const MicroSdCardDeviceModel&) = delete;
    MicroSdCardDeviceModel& operator=(const MicroSdCardDeviceModel&) = delete;
    MicroSdCardDeviceModel(MicroSdCardDeviceModel&&) = delete;
    MicroSdCardDeviceModel& operator=(MicroSdCardDeviceModel&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~MicroSdCardDeviceModel() override;

    void Initialize() override;

    [[nodiscard]] uint8_t GetSpiPort() const;
    void SetSpiPort(
        uint8_t spiPort);
    [[nodiscard]] uint8_t GetCsPin() const;
    void SetCsPin(
        uint8_t csPin);

    bool OpenFile(
        std::string_view filePath);
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
    [[nodiscard]] bool FileExists(
        std::string_view filePath);
    bool DeleteFile(
        std::string_view filePath);
    bool ListFiles(
        std::vector<std::string>& fileList);

private:
    uint8_t _spiPort;
    uint8_t _csPin;
    std::string _currentFilePath;
    bool _isFileOpen;
};
