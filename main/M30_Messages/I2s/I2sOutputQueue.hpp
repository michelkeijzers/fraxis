#pragma once

#include "../../M30_Messages/Queue.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <cstddef>

class I2sOutputQueue : public Queue
{
public:
    I2sOutputQueue() = default;

    I2sOutputQueue(
        const I2sOutputQueue&) = delete;

    I2sOutputQueue& operator=(
        const I2sOutputQueue&) = delete;

    I2sOutputQueue(
        I2sOutputQueue&&) = delete;

    I2sOutputQueue& operator=(
        I2sOutputQueue&&) = delete;

    ~I2sOutputQueue() override = default;

    struct Message
    {
        enum class EType : uint8_t
        {
            PlaySamples,
            PlayWavFile
        };

        EType type;

        union
        {
            struct
            {
                const int16_t* buffer;
                size_t length;
                Types::EI2sDeviceId deviceId;
            } playSamples;

            struct
            {
                const char* filename;
                bool stream;
            } playWavFile;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 100;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
