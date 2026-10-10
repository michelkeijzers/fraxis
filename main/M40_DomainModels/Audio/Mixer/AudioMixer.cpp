#include "AudioMixer.hpp"

AudioMixer::AudioMixer()
{
    for (auto& channel : _channels)
    {
        channel.data = nullptr;
        channel.length = 0;
        channel.position = 0;
        channel.active = false;
    }
    _mixedBuffer.resize(BUFFER_SIZE);
}

void AudioMixer::AddSound(
    const int16_t* data,
    size_t length,
    uint8_t channel)
{
    if (channel >= MAX_SIMULTANEOUS_SOUNDS)
    {
        return;
    }
    _channels[channel].data = data;
    _channels[channel].length = length;
    _channels[channel].position = 0;
    _channels[channel].active = true;
}

void AudioMixer::RemoveSound(
    uint8_t channel)
{
    if (channel >= MAX_SIMULTANEOUS_SOUNDS)
    {
        return;
    }
    _channels[channel].active = false;
}

void AudioMixer::Mix(
    int16_t* outputBuffer,
    size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        int32_t mixedSample = 0;
        for (auto& channel : _channels)
        {
            if (channel.active && channel.data && channel.position < channel.length)
            {
                mixedSample += channel.data[channel.position];
                channel.position++;
            }
        }
        outputBuffer[i] = static_cast<int16_t>(mixedSample);
    }
}

void AudioMixer::Process()
{
}
