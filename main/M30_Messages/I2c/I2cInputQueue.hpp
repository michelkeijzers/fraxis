#pragma once

#include "../Types.hpp"
#include "../Queue.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"

class I2cInputQueue : public Queue
{
public:
    I2cInputQueue() = default;

    I2cInputQueue(const I2cInputQueue&) = delete;
    I2cInputQueue& operator=(const I2cInputQueue&) = delete;
    I2cInputQueue(I2cInputQueue&&) = delete;
    I2cInputQueue& operator=(I2cInputQueue&&) = delete;

    ~I2cInputQueue() override = default;

    struct Message
    {
        enum class EType : uint8_t
        {
            JoystickDirection,
            JoystickButton,
            SystemButton
        };

        EType type;
        union 
        {
            struct
            {
                Types::EJoystickId id;
                Types::EJoystickDirection direction;
            } joystickDirection;

            struct
            {
                Types::EJoystickId id;
                bool pressed;
            } joystickButton;

            struct
            {
                bool pressed;
            } systemButton;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 25;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
