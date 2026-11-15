#include "Context.hpp"

DomainModelsContext& Context::GetDomainModels() 
{
    return _domainModelsContext; 
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
