#include "Application.hpp"
#include "../ApplicationsManager.hpp"

Application::Application(
    Context& context, 
    ApplicationsManager& applicationsManager)
:  
    _context(context), 
    _applicationsManager(applicationsManager), 
    _type(IApplication::EType::Last),
    _send(applicationsManager.GetQueueWriters()),
    _isFavorite(false),
    _isNew(false),
    _nrOfStarts(0),
    _lastStartTime(0)
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

Send& Application::GetSend()
{
    return _send;
}

bool Application::IsFavorite() const

{
    return _isFavorite; 
}

void Application::SetFavorite(
    bool isFavorite) 
{
    _isFavorite = isFavorite; 
}

bool Application::IsNew() const
{
    return _isNew;
}

void Application::SetNew(
    bool isNew)
{
    _isNew = isNew;
}

uint32_t Application::GetNrOfStarts() const
{
    return _nrOfStarts;
}

void Application::SetNrOfStarts(
    uint32_t nrOfStarts)
{
    _nrOfStarts = nrOfStarts;
}

uint32_t Application::GetLastStartTime() const
{
    return _lastStartTime;
}

void Application::SetLastStartTime(
    uint32_t lastStartTime)
{
    _lastStartTime = lastStartTime;
}
