#pragma once

#include "Mcp23017Driver.hpp"

class EspMcp23017Driver : public Mcp23017Driver
{
public:
    EspMcp23017Driver();
    ~EspMcp23017Driver() = default;
};
