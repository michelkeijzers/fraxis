#pragma once

#include "../../Core/Components/ComponentsBuilder.hpp"

class Models;
class I2c;

class WindowsComponentsBuilder : public ComponentsBuilder
{
public:
    WindowsComponentsBuilder();
    virtual ~WindowsComponentsBuilder();

    void BuildDrivers(Models& models) override;
};
