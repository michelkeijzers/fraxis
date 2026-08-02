#include "Application.hpp"
#include "../ApplicationsManager.hpp"

Application::Application(
    Context& context, ApplicationsManager& applicationsManager) 
:   _context(context), 
    _applicationsManager(applicationsManager), 
    _send(applicationsManager.GetQueueWriters())
{
}

Application::~Application() 
{
}

Context& Application::GetContext() 
{
    return _context; 
}

ApplicationsManager& Application::GetApplicationsManager() 
{
    return _applicationsManager; 
}
