#pragma once

#include "../Types.hpp"
#include "../Queue.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include <array>

class SpiInputQueue : public Queue
{
public:
    SpiInputQueue();
    ~SpiInputQueue();

    struct Message
    {
        enum class EType
        {
            MicroSdCardRead,
            TODO
        };

        EType type;
        union 
        {
            struct
            {
                std::array<uint8_t, 16384> data; // TODOSPI ; probably better to make it shorter
                uint16_t length;
            } microSdCardRead;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 25;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
