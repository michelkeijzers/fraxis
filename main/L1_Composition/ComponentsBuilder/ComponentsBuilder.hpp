#pragma once

#include "../Context/Context.hpp"

class ComponentsBuilder
{
public:
    virtual ~ComponentsBuilder();

    void Build(Context& context);

protected:
    virtual void BuildDeviceDriversContext(Context& context) = 0;
    virtual void BuildServicesContext(Context& context) = 0;

private:
    void BuildDomainModelsContext(Context& context);
    void BuildDeviceModelsContext(Context& context);
    void BuildRtosTasks(Context& context);
    void BuildRtosQueues(Context& context);
};