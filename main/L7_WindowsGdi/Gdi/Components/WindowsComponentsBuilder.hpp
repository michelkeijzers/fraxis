#pragma once

#include "../../Core/Components/ComponentsBuilder.hpp"

class Models;
class I2c;

class WindowsComponentsBuilder : public ComponentsBuilder
{
public:
    WindowsComponentsBuilder();
    ~WindowsComponentsBuilder() = default;

    void BuildDrivers(Models& models) override;
};
