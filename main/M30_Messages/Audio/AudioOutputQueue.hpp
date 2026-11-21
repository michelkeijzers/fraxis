#pragma once

#include "../../M30_Messages/Queue.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <cstddef>

class AudioOutputQueue : public Queue
{
public:
    AudioOutputQueue() = default;

    AudioOutputQueue(const AudioOutputQueue&) = delete;
    AudioOutputQueue& operator=(const AudioOutputQueue&) = delete;
    AudioOutputQueue(AudioOutputQueue&&) = delete;
    AudioOutputQueue& operator=(AudioOutputQueue&&) = delete;

    ~AudioOutputQueue() override = default;

    struct Message
    {
        enum class EType : uint8_t
        {
            PlaySamples,
            PlayWavFile,
            PlayPassiveBuzzer,
            StopPassiveBuzzer,
            SetPassiveBuzzerFrequency
        };

        EType type;

        union
        {
            struct
            {
                const int16_t* buffer;
                size_t length;
                Types::EAudioDeviceId deviceId;
            } playSamples;

            struct
            {
                const char* filename;
                bool stream;
            } playWavFile;

            struct
            {
                Types::EPassiveBuzzerId passiveBuzzerId;
            } playPassiveBuzzer;

            struct
            {
                Types::EPassiveBuzzerId passiveBuzzerId;
            } stopPassiveBuzzer;

            struct
            {
                Types::EPassiveBuzzerId passiveBuzzerId;
                uint32_t frequency;
            } setPassiveBuzzerFrequency;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 100;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
