#include "MicrophoneDeviceModel.hpp"

MicrophoneDeviceModel::MicrophoneDeviceModel()
: _i2sPort(0),
  _isRecording(false)
{
}

void MicrophoneDeviceModel::Initialize()
{
}

uint8_t MicrophoneDeviceModel::GetI2sPort() const
{
    return _i2sPort;
}

void MicrophoneDeviceModel::SetI2sPort(
    uint8_t port)
{
    _i2sPort = port;
}

bool MicrophoneDeviceModel::IsRecording() const
{
    return _isRecording;
}

void MicrophoneDeviceModel::SetRecording(
    bool recording)
{
    _isRecording = recording;
}
