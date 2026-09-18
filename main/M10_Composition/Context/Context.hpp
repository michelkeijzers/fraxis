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

    DomainModelsContext& GetDomainModels();
    DeviceModelsContext& GetDeviceModels();
    DeviceDriversContext& GetDeviceDrivers();
    ServicesContext& GetServices();
    TasksContext& GetTasks();
    QueuesContext& GetQueues();

private:
    DomainModelsContext _domainModelsContext;
    DeviceModelsContext _deviceModelsContext;
    DeviceDriversContext _deviceDriversContext;
    ServicesContext _servicesContext;
    TasksContext _tasksContext;
    QueuesContext _queuesContext;
};
