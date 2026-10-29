#pragma once

#include "../../../M90_Utilities/Dirty/Dirty.hpp"

class IoPins;

class SystemButton
{
public:
    explicit SystemButton(
        IoPins& ioPins);

    SystemButton(const SystemButton&) = delete;
    SystemButton& operator=(const SystemButton&) = delete;
    SystemButton(SystemButton&&) = delete;
    SystemButton& operator=(SystemButton&&) = delete;

    ~SystemButton() = default;

    void UpdateInput();
    bool GetState() const;

    Dirty& GetStateDirty();

private:
    IoPins& _ioPins;
    bool _state;
    Dirty _dirty;
};
