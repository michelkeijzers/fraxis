#pragma once

#include "Types.hpp"
#include "../M30_Messages/Queue.hpp"
#include "../M81_RtosServices/RtosQueue/RtosQueue.hpp"

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
                uint8_t data[16384]; // TODOSPI
                uint16_t length;
            } microSdCardRead;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 25;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
