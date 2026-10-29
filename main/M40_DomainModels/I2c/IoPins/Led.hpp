#pragma once

#include "../../../M30_Messages/Types.hpp"

class IoPins;

class Led
{
public:
    Led(
        IoPins& ioPins,
        Types::ELedId ledId);

    Led(const Led&) = delete;
    Led& operator=(const Led&) = delete;
    Led(Led&&) = delete;
    Led& operator=(Led&&) = delete;

    ~Led() = default;

    void SetState(
        bool state);
    [[nodiscard]] bool GetState() const;

private:
    IoPins& _ioPins;
    Types::ELedId _ledId;
    bool _state;
};
