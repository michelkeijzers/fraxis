#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>

namespace M60::Spi
{
    class SpiDeviceDriver;
}

class Spi;

namespace M60::Spi
{
    class IMicroSdCardDeviceDriver
    {
    public:
        virtual ~IMicroSdCardDeviceDriver() = default;

        virtual SpiDeviceDriver& GetSpiDeviceDriver() = 0;

        virtual void SetSpiDeviceDriver(
            SpiDeviceDriver& spiDeviceDriver) = 0;

        virtual bool OpenFile(
            std::string_view filePath) = 0;
        
        virtual bool CloseFile() = 0;
        
        virtual bool ReadFile(
            uint8_t* buffer,
            size_t length,
            size_t* bytesRead) = 0;
        
        virtual bool WriteFile(
            const uint8_t* buffer,
            size_t length,
            size_t* bytesWritten) = 0;
        
        virtual bool SeekFile(
            size_t offset,
            uint8_t origin) = 0;
        
        [[nodiscard]] virtual size_t GetFileSize() const = 0;
        
        [[nodiscard]] virtual bool FileExists(
            std::string_view filePath) const = 0;
        
        virtual bool DeleteFile(
            std::string_view filePath) = 0;
        
        virtual bool ListFiles(
            std::vector<std::string>& fileList) = 0;
    };
}
