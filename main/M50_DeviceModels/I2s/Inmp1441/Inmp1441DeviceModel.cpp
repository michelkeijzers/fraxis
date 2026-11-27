#include "Inmp1441DeviceModel.hpp"

namespace M50::I2s
{
    Inmp1441DeviceModel::Inmp1441DeviceModel(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities)
        :
        DeviceModel(assert, log, stringUtilities),
        _i2sPort(0),
        _isRecording(false)
    {}

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    Inmp1441DeviceModel::~Inmp1441DeviceModel() = default;

    void Inmp1441DeviceModel::Initialize()
    {}

    uint8_t Inmp1441DeviceModel::GetI2sPort() const
    {
        return _i2sPort;
    }

    void Inmp1441DeviceModel::SetI2sPort(
        uint8_t port)
    {
        _i2sPort = port;
    }

    bool Inmp1441DeviceModel::IsRecording() const
    {
        return _isRecording;
    }

    void Inmp1441DeviceModel::SetRecording(
        bool recording)
    {
        _isRecording = recording;
    }
}
