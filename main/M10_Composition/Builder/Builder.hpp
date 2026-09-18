#pragma once

#include "../Context/Context.hpp"

class Builder
{
public:
    explicit Builder(
        Context& context);
    virtual ~Builder() = default;

    Context& GetContext();
    void Build();

protected:
    virtual void BuildServicesContext() = 0;

private:
    void BuildDomainModelsContext();
    void BuildDeviceModelsContext();
    void BuildDeviceDriversContext();

    void BuildQueues();
    void BuildTasks();

    Context& _context;
};