#pragma once

#include "../../../L3_Messages/Types.hpp"

class IoPins;

class Led
{
public:
    Led(
        IoPins& ioPins,
        Types::ELedId ledId);
    ~Led();

    void SetState(
        bool state);
    bool GetState();

private:
    IoPins& _ioPins;
    Types::ELedId _ledId;
    bool _state;
};
