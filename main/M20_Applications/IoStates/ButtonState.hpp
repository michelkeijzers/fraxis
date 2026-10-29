#pragma once

class ButtonState
{
public:
    ButtonState();
    
    [[nodiscard]] bool GetState() const;
    void SetState(
        bool state);

private:
    bool _state;
};
