#pragma once

#include "../../Core/Components/ComponentsBuilder.hpp"

class EspI2c;

class EspComponentsBuilder : public ComponentsBuilder
{
public:
    EspComponentsBuilder();
    ~EspComponentsBuilder() = default;

    void BuildDrivers(Models& models) override;
};
