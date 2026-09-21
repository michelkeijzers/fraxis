#pragma once

#include "../../../DomainModel.hpp"
#include <cstdint>
#include <string>
#include <vector>

class MicroSdDeviceModel;

class MicroSd : public DomainModel
{
public:
    static constexpr size_t MAX_FILE_PATH_LENGTH = 256;
    static constexpr size_t MAX_FILE_NAME_LENGTH = 256;
    static constexpr size_t MAX_READ_BUFFER_SIZE = 512;

    MicroSd();
    ~MicroSd() = default;

    void SetDeviceModel(
        IDeviceModel& deviceModel) override;

    void Initialize();
    bool IsInitialized() const;

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

    MicroSdDeviceModel& GetMicroSdDeviceModel();

private:
    bool _isInitialized;
    MicroSdDeviceModel* _microSdDeviceModel;
};
