#pragma once

class IoPins;

class SystemButton
{
public:
    SystemButton(IoPins& ioPins);
    ~SystemButton();

    void SetState(bool state);
    bool GetState();

private:
    IoPins& _ioPins;
    bool _state;
};
