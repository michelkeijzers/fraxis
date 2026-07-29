#pragma once

#include "Builder.hpp"

// Forward declarations of Context
class Context;

class EspBuilder : public Builder
{
public:
    EspBuilder(Context& context);
    ~EspBuilder();

protected:
    void BuildDeviceDriversContext() override;
    void BuildServicesContext() override;
};
