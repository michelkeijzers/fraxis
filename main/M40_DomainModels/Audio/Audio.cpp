#include "Audio.hpp"
#include "../../M50_DeviceModels/Audio/AudioDeviceModel.hpp"

Audio::Audio()
: _audioDeviceModel(nullptr)
{
}

void Audio::SetDeviceModel(
    IDeviceModel& deviceModel)
{
    _audioDeviceModel = static_cast<AudioDeviceModel*>(&deviceModel);
}

AudioDeviceModel& Audio::GetAudioDeviceModel()
{
    return *_audioDeviceModel;
}
