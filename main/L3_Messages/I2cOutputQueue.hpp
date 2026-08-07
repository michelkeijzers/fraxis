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
            Lcd2004PredefinedCharacter,
            Lcd2004CustomCharacter,
            Lcd2004Line,
            Tm1637Value,
            Tm1637Time
        };

        EType type;

        union 
        {
            struct
            {
                uint8_t slotIndex;
                uint8_t predefinedCharacterIndex;
            } lcd2004PredefinedCharacter;
            struct
            {
                uint8_t slotIndex;
                uint8_t data[8]; // NOSONAR: pure byte data
            } lcd2004CustomCharacter;
            struct
            {
                uint8_t number;
                // Add one byte for ending \0
                char content[Lcd2004::LINE_WIDTH + 1]; // NOSONAR: No std::string in queue
            } lcd2004Line;

            struct
            {
                Types::ELedId id;
                bool state;
            } led;

            struct
            {
                Types::ETm1637Id id;
                uint32_t value;
            } tm1637Value;

            struct
            {
                Types::ETm1637Id id;
                uint8_t first;
                uint8_t second;
            } tm1637Time;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 100;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
