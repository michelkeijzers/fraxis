#include "Inmp1441DeviceDriver.hpp"
#include "../../../M90_Utilities/Assert/IAssert.hpp"
#include "../../../M30_Messages/Types.hpp"

namespace M60::I2s
{
    Inmp1441DeviceDriver::Inmp1441DeviceDriver(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities)
    :
        I2sDeviceDriver(assert, stringUtilities),
        _isRecording(false)
    {
        // No functionality required
    }

    Inmp1441DeviceDriver::~Inmp1441DeviceDriver() = default;

    void Inmp1441DeviceDriver::SetInmp1441DeviceModel(
        M50::I2s::IInmp1441DeviceModel& inmp1441DeviceModel)
    {
        _inmp1441DeviceModel = &inmp1441DeviceModel;
    }

    M50::I2s::IInmp1441DeviceModel& Inmp1441DeviceDriver::GetInmp1441DeviceModel()
    {
        return *_inmp1441DeviceModel;
    }

    void Inmp1441DeviceDriver::StartRecording()
    {
        _isRecording = true;
        Start();
    }

    void Inmp1441DeviceDriver::StopRecording()
    {
        _isRecording = false;
        Stop();
    }

    size_t Inmp1441DeviceDriver::ReadSamples(
        int16_t* buffer,
        size_t length)
    {
        if (!_isRecording)
        {
            return 0;
        }

        size_t bytesToRead = length * sizeof(int16_t);
        size_t bytesRead = Read(buffer, bytesToRead, 100);
        return bytesRead / sizeof(int16_t);
    }
}