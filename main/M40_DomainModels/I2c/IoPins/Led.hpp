#pragma once

#include "../../../M30_Messages/Types.hpp"

namespace M90::Assert
{
    class IAssert;
}

class IoPins;

class Led
{
public:
    Led(
        M90::Assert::IAssert& assert,
        IoPins& ioPins,
        Types::ELedId ledId);

    Led(
        const Led&) = delete;
    
    Led& operator=(
        const Led&) = delete;
    
    Led(
        Led&&) = delete;
    
    Led& operator=(
        Led&&) = delete;

    ~Led() = default;

    void SetState(
        bool state);
    
    [[nodiscard]] bool GetState() const;

private:
    M90::Assert::IAssert& _assert;
    
    IoPins& _ioPins;
    
    Types::ELedId _ledId;
    
    bool _state;
};
