#pragma once

#include "../Types.hpp"
#include "../Queue.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include <array>

class SpiInputQueue : public Queue
{
public:
    SpiInputQueue() = default;

    SpiInputQueue(const SpiInputQueue&) = delete;
    SpiInputQueue& operator=(const SpiInputQueue&) = delete;
    SpiInputQueue(SpiInputQueue&&) = delete;
    SpiInputQueue& operator=(SpiInputQueue&&) = delete;

    ~SpiInputQueue() override = default;

    struct Message
    {
        static constexpr uint32_t I2S_BUFFER_SIZE = 1024;

        enum class EType : uint8_t
        {
            MicroSdCardRead,
            // NOSONAR TODO Microsd
        };

        EType type = EType::MicroSdCardRead;
        union 
        {
            struct
            {
                std::array<uint8_t, I2S_BUFFER_SIZE> data = {};
                uint16_t length = 0;
            } microSdCardRead;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 25;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
