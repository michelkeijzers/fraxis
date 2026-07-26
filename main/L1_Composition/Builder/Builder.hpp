#pragma once

#include "../Context/Context.hpp"

class Builder
{
public:
    Builder(Context& context);
    virtual ~Builder();

    Context& GetContext();
    void Build();

protected:
    virtual void BuildDeviceDriversContext() = 0;
    virtual void BuildServicesContext() = 0;

private:
    void BuildDomainModelsContext();
    void BuildDeviceModelsContext();
    void BuildQueues();
    void BuildTasks();

    Context& _context;
};