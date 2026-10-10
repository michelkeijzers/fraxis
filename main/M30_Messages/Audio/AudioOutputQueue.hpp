#pragma once

#include "../../M30_Messages/Queue.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>

class AudioOutputQueue : public Queue
{
public:
    AudioOutputQueue();
    ~AudioOutputQueue();

    struct Message
    {
        enum class EType
        {
            PlaySamples,
            PlayWavFile,
            PlayBuzzer,
            StopBuzzer,
            SetBuzzerFrequency
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
                Types::EBuzzerId buzzerId;
            } playBuzzer;

            struct
            {
                Types::EBuzzerId buzzerId;
            } stopBuzzer;

            struct
            {
                Types::EBuzzerId buzzerId;
                uint32_t frequency;
            } setBuzzerFrequency;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 100;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
