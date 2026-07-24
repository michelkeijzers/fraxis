#pragma once

// #include "ComponentsBuilder/ComponentsBuilder.hpp"
#include <memory>
#include <cstdint>

class Context;

class ApplicationsManager
{
public:
    ApplicationsManager(Context& context);

private:
    Context& _context;
};