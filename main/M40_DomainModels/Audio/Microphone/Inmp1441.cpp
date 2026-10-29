#include "Inmp1441.hpp"
#include "../../../M50_DeviceModels/Audio/Microphone/MicrophoneDeviceModel.hpp"

Inmp1441::Inmp1441()
: _microphoneDeviceModel(nullptr),
  _isRecording(false)
{
}

void Inmp1441::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _microphoneDeviceModel = static_cast<MicrophoneDeviceModel*>(&deviceModel);
}

void Inmp1441::StartRecording()
{
    _isRecording = true;
}

void Inmp1441::StopRecording()
{
    _isRecording = false;
}

bool Inmp1441::IsRecording() const
{
    return _isRecording;
}

void Inmp1441::ReadSamples( // NOSONAR TODO I2S
    int16_t* /* buffer */,
    size_t /* length */)
{
    // NOSONAR TODO I2S
}

MicrophoneDeviceModel& Inmp1441::GetMicrophoneDeviceModel()
{
    return *_microphoneDeviceModel;
}
