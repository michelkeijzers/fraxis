#pragma once

#include "../../Core/Components/ComponentsBuilder.hpp"

class WindowsComponentsBuilder : public ComponentsBuilder
{
public:
    WindowsComponentsBuilder();
    ~WindowsComponentsBuilder() = default;

    void BuildDrivers() override;
};
