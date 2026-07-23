#pragma once

#include <memory>

#include "DomainModelsContext.hpp"
#include "DeviceModelsContext.hpp"
#include "DeviceDriversContext.hpp"
#include "ServicesContext.hpp"

class Context
{
public:
    Context();
    ~Context();

    // Accessors for all sub-contexts
    DomainModelsContext& GetDomainModels() { return _domainModelsContext; }
    DeviceModelsContext& GetDeviceModels() { return _deviceModelsContext; }
    DeviceDriversContext& GetDeviceDrivers() { return _deviceDriversContext; }
    ServicesContext& GetServices() { return _servicesContext; }

    // Public members (optional, but convenient)
    DomainModelsContext _domainModelsContext;
    DeviceModelsContext _deviceModelsContext;
    DeviceDriversContext _deviceDriversContext;
    ServicesContext _servicesContext;
};
