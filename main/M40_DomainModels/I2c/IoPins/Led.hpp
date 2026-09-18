#pragma once

#include "../../../M30_Messages/Types.hpp"

class IoPins;

class Led
{
public:
    Led(
        IoPins& ioPins,
        Types::ELedId ledId);
    ~Led() = default;

    void SetState(
        bool state);
    bool GetState() const;

private:
    IoPins& _ioPins;
    Types::ELedId _ledId;
    bool _state;
};
