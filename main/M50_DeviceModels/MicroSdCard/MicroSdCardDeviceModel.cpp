#include "MicroSdCardDeviceModel.hpp"

MicroSdCardDeviceModel::MicroSdCardDeviceModel()
: 
    _spiPort(0),
    _csPin(0),
    _isFileOpen(false)
{
}

// Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
MicroSdCardDeviceModel::~MicroSdCardDeviceModel() = default;

void MicroSdCardDeviceModel::Initialize()
{
    // NOSONAR TODO MICRO_SD
}

uint8_t MicroSdCardDeviceModel::GetSpiPort() const
{
    return _spiPort;
}

void MicroSdCardDeviceModel::SetSpiPort(
    uint8_t spiPort)
{
    _spiPort = spiPort;
}

uint8_t MicroSdCardDeviceModel::GetCsPin() const
{
    return _csPin;
}

void MicroSdCardDeviceModel::SetCsPin(
    uint8_t csPin)
{
    _csPin = csPin;
}

// NOSONAR TODO MICRO_SD
bool MicroSdCardDeviceModel::OpenFile(
    std::string_view filePath)
{
    _currentFilePath = filePath;
    _isFileOpen = true;
    return true;
}

// NOSONAR TODO MICRO_SD
bool MicroSdCardDeviceModel::CloseFile()
{
    _isFileOpen = false;
    _currentFilePath.clear();
    return true;
}

// NOSONAR TODO MICRO_SD
bool MicroSdCardDeviceModel::ReadFile( // NOSONAR S5817: const
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4100) // Unreferenced parameter
#endif
uint8_t* buffer, // NOSONAR S1172 Unused parameter
    size_t length, // NOSONAR S1172 Unused parameter
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
size_t* bytesRead)
{
    if (bytesRead != nullptr)
    {
        *bytesRead = 0;
    }
    return false;
}

// NOSONAR TODO MICRO_SD
bool MicroSdCardDeviceModel::WriteFile( // NOSONAR S5817: const
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4100) // Unreferenced parameter
#endif
    const uint8_t* buffer, // NOSONAR S1172 Unused parameter
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
    size_t length,
    size_t* bytesWritten)
{
    if (bytesWritten != nullptr)
    {
        *bytesWritten = length;
    }
    return true;
}

// NOSONAR TODO MICRO_SD
bool MicroSdCardDeviceModel::SeekFile( // NOSONAR S5817: const
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4100) // Unreferenced parameter
#endif
    size_t offset, // NOSONAR: 1172 Unused parameter
    uint8_t origin) // NOSONAR: 1172 Unused parameter
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
{
    return true;
}

// NOSONAR TODO MICRO_SD
size_t MicroSdCardDeviceModel::GetFileSize() // NOSONAR S5817: const
{
    return 0;
}

// NOSONAR TODO MICRO_SD
bool MicroSdCardDeviceModel::FileExists( // NOSONAR S5817: const
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4100) // Unreferenced parameter
#endif
    std::string_view filePath) // NOSONAR S1172 Unused parameter
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
{
    return false;
}

// NOSONAR TODO MICRO_SD
bool MicroSdCardDeviceModel::DeleteFile( // NOSONAR S5817: const
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4100) // Unreferenced parameter
#endif
std::string_view filePath) // NOSONAR S1172 Unused parameter
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
{
    return false;
}

// NOSONAR TODO MICRO_SD
bool MicroSdCardDeviceModel::ListFiles( // NOSONAR S5817: const
    std::vector<std::string>& fileList)
{
    fileList.clear();
    return true;
}
