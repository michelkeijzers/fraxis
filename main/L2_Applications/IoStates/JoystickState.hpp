#pragma once

class JoystickState
{
public:
    JoystickState();
    
    enum class EDirection
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

    EDirection GetDirection() const;
    void SetDirection(EDirection direction);

    bool GetButtonState() const;
    void SetButtonState(bool state);

private:
    EDirection _direction;
    bool _buttonState;
};
