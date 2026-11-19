#pragma once

#include "Builder.hpp"

// Forward declarations of Context
class Context;

class WindowsBuilder : public Builder
{
public:
    explicit WindowsBuilder() = default;

    ~WindowsBuilder() = default;

protected:
    void BuildServicesContext() override;
};
