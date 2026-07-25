#pragma once

#include "../L2_Applications/Queues/Queue.hpp"
#include "../L2_Applications/IoStates/IoStates.hpp"
#include "../L2_Applications/IoStates/JoystickState.hpp"
#include "../L4_DomainModels/I2c/IoPins/Joystick.hpp"
#include "../L8_Services/RtosQueue/RtosQueue.hpp"

class InputQueue : public Queue
{
public:
    InputQueue();
    ~InputQueue();

    struct InputMessage
    {
        enum class EType
        {
            JoystickDirection,
            JoystickButton,
            SystemButton,
        };

        EType type;

        union 
        {
            struct
            {
                IoStates::EJoystickId joystickId;
                Joystick::EDirection direction;
            } joystickDirection;
            struct
            {
                IoStates::EJoystickId id;
                bool pressed;
            } joystickButton;

            struct
            {
                bool pressed;
            } systemButton;
        };
    };
};
