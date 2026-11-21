#pragma once

#include "../../M30_Messages/Queue.hpp"
#include "../../M30_Messages/Types.hpp"
#include <cstdint>
#include <cstddef>

class PassiveBuzzerQueue : public Queue
{
public:
    PassiveBuzzerQueue() = default;

    PassiveBuzzerQueue(
        const PassiveBuzzerQueue&) = delete;

    PassiveBuzzerQueue& operator=(
        const PassiveBuzzerQueue&) = delete;

    PassiveBuzzerQueue(
        PassiveBuzzerQueue&&) = delete;

    PassiveBuzzerQueue& operator=(
        PassiveBuzzerQueue&&) = delete;

    ~PassiveBuzzerQueue() override = default;

    struct Message
    {
        enum class EType : uint8_t
        {
            Play,
            Stop,
            SetFrequency
        };

        EType type;

        union
        {
            struct
            {
                Types::EPassiveBuzzerId passiveBuzzerId;
            } play;

            struct
            {
                Types::EPassiveBuzzerId passiveBuzzerId;
            } stop;

            struct
            {
                Types::EPassiveBuzzerId passiveBuzzerId;
                uint32_t frequency;
            } setFrequency;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 10;

    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
