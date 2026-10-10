#pragma once

#include "../../M40_DomainModels/Audio/Microphone/Inmp1441.hpp"
#include "../../M40_DomainModels/Audio/Dac/Max53987a.hpp"
#include "../../M40_DomainModels/Audio/Buzzer/Buzzer.hpp"
#include "../../M30_Messages/Types.hpp"

#include <cstdint>

class Context;

class AudioTaskDeviceDriversDelegate
{
public:
    explicit AudioTaskDeviceDriversDelegate(
        Context& context);
    ~AudioTaskDeviceDriversDelegate() = default;

    void Initialize();

    void Run();

private:
    Context& _context;
};
