#pragma once

#include "../L3_Messages/Types.hpp"

#include <cstdint>

class Context;

class LedStripsTaskDeviceDriversDelegate
{
public:
    static constexpr uint32_t WS28XX_WRITE_FREQUENCY = 60; // Hz

    LedStripsTaskDeviceDriversDelegate(Context& context);
    ~LedStripsTaskDeviceDriversDelegate();

    void Initialize();

    void Run();

private:
    Context& _context;

    uint64_t _lastWs28xxWriteUs;
};
