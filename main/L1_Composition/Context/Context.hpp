#pragma once

#include <memory>

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
    ~Context();

    DomainModelsContext& GetDomainModels() { return _domainModelsContext; }
    DeviceModelsContext& GetDeviceModels() { return _deviceModelsContext; }
    DeviceDriversContext& GetDeviceDrivers() { return _deviceDriversContext; }
    ServicesContext& GetServices() { return _servicesContext; }
    TasksContext& GetTasks() { return _tasksContext; }
    QueuesContext& GetQueues() { return _queuesContext; }

private:
    DomainModelsContext _domainModelsContext;
    DeviceModelsContext _deviceModelsContext;
    DeviceDriversContext _deviceDriversContext;
    ServicesContext _servicesContext;
    TasksContext _tasksContext;
    QueuesContext _queuesContext;
};
