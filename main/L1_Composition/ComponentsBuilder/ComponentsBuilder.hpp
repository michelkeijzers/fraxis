#pragma once

#include "../Context/Context.hpp"

class ComponentsBuilder
{
public:
    virtual ~ComponentsBuilder();

    void Build(Context& context);

protected:
    virtual void BuildDomainModelsContext(Context& context) = 0;
    virtual void BuildDeviceModelsContext(Context& context) = 0;
    virtual void BuildDeviceDriversContext(Context& context) = 0;
    virtual void BuildServicesContext(Context& context) = 0;
};