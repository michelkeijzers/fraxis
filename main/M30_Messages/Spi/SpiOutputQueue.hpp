#pragma once

#include "../Types.hpp"
#include "../Queue.hpp"
#include "../../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"

class SpiOutputQueue : public Queue
{
public:
    static constexpr uint16_t SPI_BUFFER_SIZE = 512;

    SpiOutputQueue() = default;

    SpiOutputQueue(const SpiOutputQueue&) = delete;
    SpiOutputQueue& operator=(const SpiOutputQueue&) = delete;
    SpiOutputQueue(SpiOutputQueue&&) = delete;
    SpiOutputQueue& operator=(SpiOutputQueue&&) = delete;

    ~SpiOutputQueue() override = default;

    struct Message
    {
        enum class EType : uint8_t
        {
            MicroSdCardWrite
        };

        EType type = EType::MicroSdCardWrite;

        union 
        {
            struct
            {
                std::array<uint8_t, SPI_BUFFER_SIZE> data = {};
                uint16_t length = 0;
            } microSdCardWrite;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 100;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
