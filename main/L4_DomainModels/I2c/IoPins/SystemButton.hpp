#pragma once

#include "../../../L9_Utilities/Dirty/Dirty.hpp"

class IoPins;

class SystemButton
{
public:
    SystemButton(IoPins& ioPins);
    ~SystemButton();

    void UpdateInput();
    bool GetState();

    Dirty& GetStateDirty();

private:
    IoPins& _ioPins;
    bool _state;
    Dirty _dirty;
};
