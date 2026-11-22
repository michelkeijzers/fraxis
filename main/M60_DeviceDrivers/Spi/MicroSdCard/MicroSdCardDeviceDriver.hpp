#pragma once

#include "IMicroSdCardDeviceDriver.hpp"
#include "../../DeviceDriver.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::String
{
    class IStringUtilities;
}

namespace M60::Spi
{
    class ISpiDeviceDriver;
    class ISpi;

    class MicroSdCardDeviceDriver : public DeviceDriver, public IMicroSdCardDeviceDriver
    {
    public:
        MicroSdCardDeviceDriver(
            ISpiDeviceDriver& spiDeviceDriver,
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        MicroSdCardDeviceDriver(
            const MicroSdCardDeviceDriver&) = delete;
        
        MicroSdCardDeviceDriver& operator=(
            const MicroSdCardDeviceDriver&) = delete;
        
        MicroSdCardDeviceDriver(
            MicroSdCardDeviceDriver&&) = delete;
        
        MicroSdCardDeviceDriver& operator=(
            MicroSdCardDeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~MicroSdCardDeviceDriver() override;

        void Initialize() override;

        bool OpenFile(
            std::string_view filePath) override ;
        
        bool CloseFile() override;
        
        bool ReadFile(
            uint8_t* buffer,
            size_t length,
            size_t* bytesRead) override;
        
        bool WriteFile(
            const uint8_t* buffer,
            size_t length,
            size_t* bytesWritten) override;
        
        bool SeekFile(
            size_t offset,
            uint8_t origin) override;
        
        [[nodiscard]] size_t GetFileSize() const override;
        
        [[nodiscard]] bool FileExists(
            std::string_view filePath) const override;
        
        bool DeleteFile(
            std::string_view filePath) override;
        
        bool ListFiles(
            std::vector<std::string>& fileList) override;

    private:
        ISpiDeviceDriver& _spiDeviceDriver;
    };
}
