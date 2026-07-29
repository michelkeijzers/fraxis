#pragma once

class Types
{
public:
    enum class EType
    {
        JoystickDirection,
        JoystickButton,
        SystemButton,
    };

    enum class EJoystickId
    {
        Player1 = 0,
        Player2 = 1
    };

    enum class EJoystickDirection
    {
        Centered = 0,
        Up = 1, 
        UpRight = 2,
        Right = 3,
        DownRight = 4,
        Down = 5,
        DownLeft = 6,
        Left = 7,
        UpLeft = 8
    };

    enum class ELedId
    {
        Player1 = 0,
        Player2 = 1,
        PlayPause = 2,
        Select = 3,
        Setup = 4
    };

    enum class ETm1637Id
    {
        CentralPanel = 0,
        Player1 = 1,
        Player2 = 2
    };
};
