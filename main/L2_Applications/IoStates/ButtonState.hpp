#pragma once

class ButtonState
{
public:
    ButtonState();
    
    bool GetState() const;
    void SetState(bool state);

private:
    bool _state;
};
