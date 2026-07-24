#pragma once

#include "../L2_Applications/Queue.hpp"
#include "../L2_Applications/IoStates/IoStates.hpp"
#include "../L2_Applications/IoStates/JoystickState.hpp"

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
                JoystickState::EDirection direction;
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
