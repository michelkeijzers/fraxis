#pragma once

#include "ComponentsBuilder.hpp"

// Forward declarations of Context
class Context;

class EspComponentsBuilder : public ComponentsBuilder
{
public:
    EspComponentsBuilder(Context& context);
    ~EspComponentsBuilder() override;

protected:
    void BuildDeviceDriversContext() override;
    void BuildServicesContext() override;
};
