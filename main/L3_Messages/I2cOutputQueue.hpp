#pragma once

#include "Types.hpp"
#include "../L3_Messages/Queue.hpp"
#include "../L4_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"

class I2cOutputQueue : public Queue
{
public:
    I2cOutputQueue();
    ~I2cOutputQueue();

    struct Message
    {
        enum class EType
        {
            Led,
            Lcd2004Line,
            Tm1637Value,
            Tm1637Time
        };

        EType type;

        union 
        {
            struct
            {
                uint8_t lineNumber;
                // Add one byte for ending \0
                char lineContent[Lcd2004::LINE_WIDTH + 1]; // NOSONAR: No std::string in queue
            } lcd2004Line;

            struct
            {
                Types::ELedId ledId;
                bool state;
            } led;

            struct
            {
                Types::ETm1637Id tm1637Id;
                uint32_t value;
            } tm1637Value;

            struct
            {
                Types::ETm1637Id tm1637Id;
                uint8_t first;
                uint8_t second;
            } tm1637Time;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 100;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
