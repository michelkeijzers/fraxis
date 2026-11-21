#pragma once

#include "../Types.hpp"
#include "../Queue.hpp"
#include "../../M40_DomainModels/SevenSegmentsDisplays/Tm1637.hpp"
#include <array>

class SevenSegmentsDisplaysQueue : public Queue
{
public:
    SevenSegmentsDisplaysQueue() = default;

    SevenSegmentsDisplaysQueue(
        const SevenSegmentsDisplaysQueue&) = delete;

    SevenSegmentsDisplaysQueue& operator=(
        const SevenSegmentsDisplaysQueue&) = delete;

    SevenSegmentsDisplaysQueue(
        SevenSegmentsDisplaysQueue&&) = delete;

    SevenSegmentsDisplaysQueue& operator=(
        SevenSegmentsDisplaysQueue&&) = delete;

    ~SevenSegmentsDisplaysQueue() override = default;

    struct Message
    {
        enum class EType : uint8_t
        {
            Tm1637Enable,
            Tm1637Brightness,
            Tm1637Value,
            Tm1637Time
        };

        EType type = EType::Tm1637Enable;

        union
        {
            struct
            {
                Types::ELedId id = Types::ELedId::Player1;
                bool state = false;
            } led;

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
