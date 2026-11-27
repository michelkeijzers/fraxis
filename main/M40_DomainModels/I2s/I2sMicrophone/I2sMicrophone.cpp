#include "I2sMicrophone.hpp"
#include "../../../M50_DeviceModels/I2s/Inmp1441/Inmp1441DeviceModel.hpp"

I2sMicrophone::I2sMicrophone(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log)
: 
    DomainModel(assert, log),
    _inmp1441DeviceModel(nullptr),
    _isRecording(false)
{
    // No functionality required.
}

void I2sMicrophone::SetDeviceModel(
    M50::IDeviceModel& deviceModel)
{
    _inmp1441DeviceModel = static_cast<M50::I2s::Inmp1441DeviceModel*>(&deviceModel);
}

void I2sMicrophone::StartRecording()
{
    _isRecording = true;
}

void I2sMicrophone::StopRecording()
{
    _isRecording = false;
}

bool I2sMicrophone::IsRecording() const
{
    return _isRecording;
}

void I2sMicrophone::ReadSamples( // NOSONAR TODO I2S
    int16_t* /* buffer */,
    size_t /* length */)
{
    // NOSONAR TODO I2S
}

M50::I2s::Inmp1441DeviceModel& I2sMicrophone::GetInmp1441DeviceModel()
{
    return *_inmp1441DeviceModel;
}
