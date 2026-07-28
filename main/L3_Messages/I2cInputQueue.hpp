#pragma once

#include "Types.hpp"
#include "../L2_Applications/Queues/Queue.hpp"
#include "../L8_Services/RtosQueue/RtosQueue.hpp"

class I2cInputQueue : public Queue
{
public:
    I2cInputQueue();
    ~I2cInputQueue();

    struct InputMessage
    {
        enum class EType
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
};
