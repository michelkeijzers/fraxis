#pragma once

#include "ComponentsBuilder.hpp"

// Forward declarations of Context
class Context;

class EspComponentsBuilder : public ComponentsBuilder
{
public:
    EspComponentsBuilder();
    ~EspComponentsBuilder() override;

protected:
    void BuildDomainModelsContext(Context& context) override;
    void BuildDeviceModelsContext(Context& context) override;
    void BuildDeviceDriversContext(Context& context) override;
    void BuildServicesContext(Context& context) override;
};
