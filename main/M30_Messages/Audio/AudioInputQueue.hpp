#pragma once

#include "../../M30_Messages/Queue.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>

class AudioInputQueue : public Queue
{
public:
    AudioInputQueue();
    ~AudioInputQueue();

    struct Message
    {
        enum class EType
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
