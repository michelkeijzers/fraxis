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
    Context() = default;

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
    
    ServicesContext& GetServices();
    
    TasksContext& GetTasks();
    
    QueuesContext& GetQueues();

private:
    DomainModelsContext _domainModelsContext;
    
    DeviceModelsContext _deviceModelsContext;
    
    ServicesContext _servicesContext;
    
    UtilitiesContext _utilitiesContext;

    TasksContext _tasksContext;
    
    QueuesContext _queuesContext;
};
