#pragma once

#include "Builder.hpp"

// Forward declarations of Context
class Context;

class WindowsBuilder : public Builder
{
public:
    explicit WindowsBuilder(
        Context& context);
    ~WindowsBuilder() = default;

protected:
    void BuildServicesContext() override;
};
