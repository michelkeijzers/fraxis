#pragma once

#include "Types.hpp"
#include "../M30_Messages/Queue.hpp"
#include "../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"

class SpiOutputQueue : public Queue
{
public:
    SpiOutputQueue();
    ~SpiOutputQueue();

    struct Message
    {
        enum class EType
        {
            MicroSdCardWrite
        };

        EType type;

        union 
        {
            struct
            {
                uint8_t data[4000]; //TODOSD
                uint16_t length;
            } microSdCardWrite;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 100;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
