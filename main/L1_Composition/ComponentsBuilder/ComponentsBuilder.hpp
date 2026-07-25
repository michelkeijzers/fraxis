#pragma once

#include "../Context/Context.hpp"

class ComponentsBuilder
{
public:
    ComponentsBuilder(Context& context);
    virtual ~ComponentsBuilder();

    void Build(Context& context);

protected:
    virtual void BuildDeviceDriversContext() = 0;
    virtual void BuildServicesContext() = 0;

    Context& GetContext();

private:
    void BuildDomainModelsContext();
    void BuildDeviceModelsContext();
    void BuildQueues();
    void BuildTasks();
    void CreateLinks();

    Context& _context;
};