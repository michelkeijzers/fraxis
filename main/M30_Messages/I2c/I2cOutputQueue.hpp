#pragma once

#include "../Types.hpp"
#include "../Queue.hpp"
#include "../../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include <array>

class I2cOutputQueue : public Queue
{
public:
    I2cOutputQueue() = default;

    I2cOutputQueue(const I2cOutputQueue&) = delete;
    I2cOutputQueue& operator=(const I2cOutputQueue&) = delete;
    I2cOutputQueue(I2cOutputQueue&&) = delete;
    I2cOutputQueue& operator=(I2cOutputQueue&&) = delete;

    ~I2cOutputQueue() override = default;

    struct Message
    {
        enum class EType : uint8_t
        {
            Led,
            Lcd2004PredefinedCharacter,
            Lcd2004CustomCharacter,
            Lcd2004Line,
            Tm1637Enable,
            Tm1637Brightness,
            Tm1637Value,
            Tm1637Time
        };

        EType type = EType::Led;

        union 
        {
            struct
            {
                Types::ELedId id = Types::ELedId::Player1;
                bool state = false;
            } led;
                        struct
            {
                uint8_t slotIndex = 0;
                uint8_t predefinedCharacterIndex = 0;
            } lcd2004PredefinedCharacter;

            struct
            {
                uint8_t slotIndex = 0;
                std::array<uint8_t, Lcd2004::CUSTOM_CHARACTER_DATA_SIZE> data = {};
            } lcd2004CustomCharacter;

            struct
            {
                uint8_t number = 0;
                // Add one byte for ending \0
                std::array<char, Lcd2004::LINE_WIDTH + 1> content = {};
            } lcd2004Line;

            struct
            {
                Types::ETm1637Id id = Types::ETm1637Id::Player1;
                bool on = false;
            } tm1637Enable;

            struct
            {
                Types::ETm1637Id id = Types::ETm1637Id::Player1;
                uint8_t brightness = 0;
            } tm1637Brightness;
            struct
            {
                Types::ETm1637Id id = Types::ETm1637Id::Player1;
                uint32_t value = 0;
            } tm1637Value;

            struct
            {
                Types::ETm1637Id id = Types::ETm1637Id::Player1;
                uint8_t first = 0;
                uint8_t second = 0;
            } tm1637Time;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 100;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
