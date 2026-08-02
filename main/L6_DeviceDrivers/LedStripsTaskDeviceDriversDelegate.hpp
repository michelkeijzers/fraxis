#pragma once

#include "../L3_Messages/Types.hpp"

#include <cstdint>

class Context;

class LedStripsTaskDeviceDriversDelegate
{
public:
    LedStripsTaskDeviceDriversDelegate(Context& context);
    ~LedStripsTaskDeviceDriversDelegate();

    void Initialize();

    void Run();

private:
    Context& _context;
};
