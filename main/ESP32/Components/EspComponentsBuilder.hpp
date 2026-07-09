#pragma once

#include "../../Core/Components/ComponentsBuilder.hpp"

class EspI2c;

class EspComponentsBuilder : public ComponentsBuilder
{
public:
    EspComponentsBuilder();
    ~EspComponentsBuilder() = default;

    void BuildDrivers() override;

private:
    EspI2c* _espI2c; // TODO: Create a generic I2c class (also for windows).
};
