#pragma once

#include "../../M30_Messages/Queue.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <cstddef>

class AudioInputQueue : public Queue
{
public:
    AudioInputQueue() = default;

    AudioInputQueue(const AudioInputQueue&) = delete;
    AudioInputQueue& operator=(const AudioInputQueue&) = delete;
    AudioInputQueue(AudioInputQueue&&) = delete;
    AudioInputQueue& operator=(AudioInputQueue&&) = delete;

    ~AudioInputQueue() override = default;

    struct Message
    {
        enum class EType : uint8_t
        {
            SamplesRecorded
        };

        EType type;

        union
        {
            struct
            {
                int16_t* buffer;
                size_t length;
                Types::EAudioDeviceId deviceId;
            } samplesRecorded;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 100;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
