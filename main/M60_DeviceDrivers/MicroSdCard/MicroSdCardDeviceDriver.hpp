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
    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    MicroSdCardDeviceDriver();

    MicroSdCardDeviceDriver(const MicroSdCardDeviceDriver&) = delete;
    MicroSdCardDeviceDriver& operator=(const MicroSdCardDeviceDriver&) = delete;
    MicroSdCardDeviceDriver(MicroSdCardDeviceDriver&&) = delete;
    MicroSdCardDeviceDriver& operator=(MicroSdCardDeviceDriver&&) = delete;

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    ~MicroSdCardDeviceDriver() override;

    SpiDeviceDriver& GetSpiDeviceDriver();
    void SetSpiDeviceDriver(
        SpiDeviceDriver& spiDeviceDriver);

    void Initialize() override;

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
    [[nodiscard]] size_t GetFileSize() const;
    [[nodiscard]] bool FileExists(
        std::string_view filePath) const;
    bool DeleteFile(
        std::string_view filePath);
    bool ListFiles(
        std::vector<std::string>& fileList);

private:
    SpiDeviceDriver* _spiDeviceDriver;
};
