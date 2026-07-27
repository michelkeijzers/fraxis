#pragma once

class SystemButton
{
public:
    SystemButton();
    ~SystemButton();

    void SetState(bool state);
    bool GetState();

private:
    bool _state;
};
