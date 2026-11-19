#include "Inmp1441.hpp"
#include "../../../M50_DeviceModels/Audio/Inmp1441/Inmp1441DeviceModel.hpp"

Inmp1441::Inmp1441()
: _inmp1441DeviceModel(nullptr),
  _isRecording(false)
{
}

void Inmp1441::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _inmp1441DeviceModel = static_cast<Inmp1441DeviceModel*>(&deviceModel);
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

Inmp1441DeviceModel& Inmp1441::GetInmp1441DeviceModel()
{
    return *_inmp1441DeviceModel;
}
