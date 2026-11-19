#include "Context.hpp"

Context::Context()
:
    _utilitiesContext(),
    _deviceDriversContext(_utilitiesContext.GetAssert())
{
    // No actions required
}

DomainModelsContext& Context::GetDomainModels() 
{
    return _domainModelsContext; 
}

DeviceDriversContext& Context::GetDeviceDrivers()
{
    return _deviceDriversContext;
}

DeviceModelsContext& Context::GetDeviceModels() 
{ 
    return _deviceModelsContext;
}

ServicesContext& Context::GetServices() 
{ 
    return _servicesContext; 
}

UtilitiesContext &Context::GetUtilities() 
{
    return _utilitiesContext;
}

TasksContext &Context::GetTasks() {
    return _tasksContext; 
}

QueuesContext& Context::GetQueues() 
{ 
    return _queuesContext;
}
