#pragma once

#include <memory>

#include "UtilitiesContext.hpp"
#include "DomainModelsContext.hpp"
#include "DeviceModelsContext.hpp"
#include "DeviceDriversContext.hpp"
#include "ServicesContext.hpp"
#include "TasksContext.hpp"
#include "QueuesContext.hpp"

class Context
{
public:
    Context();

    Context(
        const Context&) = default;

    Context& operator=(
        const Context&) = default;

    Context(
        Context&&) = default;

    Context& operator=(
        Context&&) = default;

    ~Context() = default;

    UtilitiesContext &GetUtilities();

    DomainModelsContext& GetDomainModels();

    DeviceModelsContext &GetDeviceModels();

    DeviceDriversContext& GetDeviceDrivers();
    
    ServicesContext& GetServices();
    
    TasksContext& GetTasks();
    
    QueuesContext& GetQueues();

private:
    UtilitiesContext _utilitiesContext;

    ServicesContext _servicesContext;

    DeviceModelsContext _deviceModelsContext;

    DomainModelsContext _domainModelsContext;

    DeviceDriversContext _deviceDriversContext;
    
    TasksContext _tasksContext;
    
    QueuesContext _queuesContext;
};
