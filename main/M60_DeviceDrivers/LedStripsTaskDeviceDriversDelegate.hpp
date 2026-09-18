#pragma once

#include "../M30_Messages/Types.hpp"

#include <cstdint>

class Context;

class LedStripsTaskDeviceDriversDelegate
{
public:
    explicit LedStripsTaskDeviceDriversDelegate(Context& context);
    ~LedStripsTaskDeviceDriversDelegate() = default;

    void Initialize();

    void Run();

private:
    Context& _context;
};
