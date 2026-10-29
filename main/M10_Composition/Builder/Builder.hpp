#pragma once

#include "../Context/Context.hpp"

class Builder
{
public:
    explicit Builder(
        Context& context);

    Builder(const Builder&) = delete;
    Builder& operator=(const Builder&) = delete;
    Builder(Builder&&) = delete;
    Builder& operator=(Builder&&) = delete;

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