#pragma once

class Led
{
public:
    Led();
    ~Led();

    void SetState(bool state);
    bool GetState();

private:
    bool _state;
};
