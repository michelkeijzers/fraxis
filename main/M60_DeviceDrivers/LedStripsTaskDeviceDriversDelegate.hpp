#pragma once

#include "../M30_Messages/Types.hpp"

#include <cstdint>

class Context;

class LedStripsTaskDeviceDriversDelegate
{
public:
    explicit LedStripsTaskDeviceDriversDelegate(Context& context);

    LedStripsTaskDeviceDriversDelegate(const LedStripsTaskDeviceDriversDelegate&) = delete;
    LedStripsTaskDeviceDriversDelegate& operator=(const LedStripsTaskDeviceDriversDelegate&) = 
        delete;
    LedStripsTaskDeviceDriversDelegate(LedStripsTaskDeviceDriversDelegate&&) = delete;
    LedStripsTaskDeviceDriversDelegate& operator=(LedStripsTaskDeviceDriversDelegate&&) = delete;

    ~LedStripsTaskDeviceDriversDelegate() = default;

    void Initialize();

    void Run();

private:
    Context& _context;
};
