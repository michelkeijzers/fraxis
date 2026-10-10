#pragma once

#include <cstdint>
#include <vector>
#include <array>

class AudioMixer
{
public:
    static constexpr uint8_t MAX_SIMULTANEOUS_SOUNDS = 3;
    static constexpr uint32_t SAMPLE_RATE = 16000;
    static constexpr uint16_t BUFFER_SIZE = 512;

    AudioMixer();
    ~AudioMixer() = default;

    void AddSound(
        const int16_t* data,
        size_t length,
        uint8_t channel);

    void RemoveSound(
        uint8_t channel);

    void Mix(
        int16_t* outputBuffer,
        size_t length);

    void Process();

private:
    struct SoundChannel
    {
        const int16_t* data;
        size_t length;
        size_t position;
        bool active;
    };

    std::array<SoundChannel, MAX_SIMULTANEOUS_SOUNDS> _channels;
    std::vector<int16_t> _mixedBuffer;
};
