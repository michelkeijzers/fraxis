#pragma once

#include <memory>

#include "DomainModelsContext.hpp"
#include "DeviceModelsContext.hpp"
#include "DeviceDriversContext.hpp"
#include "ServicesContext.hpp"
#include "RtosTasksContext.hpp"
#include "RtosQueuesContext.hpp"

class Context
{
public:
    Context();
    ~Context();

    DomainModelsContext& GetDomainModels() { return _domainModelsContext; }
    DeviceModelsContext& GetDeviceModels() { return _deviceModelsContext; }
    DeviceDriversContext& GetDeviceDrivers() { return _deviceDriversContext; }
    ServicesContext& GetServices() { return _servicesContext; }
    RtosTasksContext& GetRtosTasks() { return _rtosTasksContext; }
    RtosQueuesContext& GetRtosQueues() { return _rtosQueuesContext; }

private:
    DomainModelsContext _domainModelsContext;
    DeviceModelsContext _deviceModelsContext;
    DeviceDriversContext _deviceDriversContext;
    ServicesContext _servicesContext;
    RtosTasksContext _rtosTasksContext;
    RtosQueuesContext _rtosQueuesContext;
};
