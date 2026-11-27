#pragma once

#include "../../M30_Messages/Queue.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
// Do not remove cstddef, needed for size_t in ESP build.
#include <cstddef>

class I2sInputQueue : public Queue
{
public:
    I2sInputQueue() = default;

    I2sInputQueue(
        const I2sInputQueue&) = delete;

    I2sInputQueue& operator=(
        const I2sInputQueue&) = delete;

    I2sInputQueue(
        I2sInputQueue&&) = delete;

    I2sInputQueue& operator=(
        I2sInputQueue&&) = delete;

    ~I2sInputQueue() override = default;

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
                Types::EI2sDeviceId deviceId;
            } samplesRecorded;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 100;

    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
