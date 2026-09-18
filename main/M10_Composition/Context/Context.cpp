#include "Context.hpp"

Context::Context()
{
}

Context::~Context()
{
}

DomainModelsContext& Context::GetDomainModels() 
{
    return _domainModelsContext; 
}

DeviceModelsContext& Context::GetDeviceModels() 
{ 
    return _deviceModelsContext;
}

DeviceDriversContext& Context::GetDeviceDrivers() 
{
    return _deviceDriversContext; 
}

ServicesContext& Context::GetServices() 
{ 
    return _servicesContext; 
}

TasksContext& Context::GetTasks() 
{
    return _tasksContext; 
}

QueuesContext& Context::GetQueues() 
{ 
    return _queuesContext;
}
