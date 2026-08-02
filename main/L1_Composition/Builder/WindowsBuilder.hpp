#pragma once

#include "Builder.hpp"

// Forward declarations of Context
class Context;

class WindowsBuilder : public Builder
{
public:
    WindowsBuilder(
        Context& context);
    ~WindowsBuilder();

protected:
    void BuildServicesContext() override;
};
