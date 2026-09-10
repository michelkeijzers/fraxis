#include "Application.hpp"
#include "../ApplicationsManager.hpp"
#include "../../L6_DeviceDrivers/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../../L9_Utilities/String/StringUtilities.hpp"

Application::Application(
    Context& context,
    ApplicationsManager& applicationsManager)
    :
    _context(context),
    _applicationsManager(applicationsManager),
    _type(IApplication::EType::Last),
    _state(IApplication::EState::Idle),
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

IApplication::EState Application::GetState() const
{
    return _state;
}

void Application::Start()
{
    _state = EState::Running;
    DisplayName();
}

void Application::Pause()
{
    _state = EState::Paused;
}

void Application::Resume()
{
    _state = EState::Running;
    DisplayName();
}

void Application::Stop()
{
    _state = EState::Idle;
}

void Application::DisplayName()
{
    Send& send = GetSend();
    send.Line(0, StringUtilities::LeftAlign(GetName(), Lcd2004::LINE_WIDTH));
    send.Line(1, StringUtilities::LeftAlign("", Lcd2004::LINE_WIDTH));
    send.Line(2, StringUtilities::LeftAlign("", Lcd2004::LINE_WIDTH));
    send.Line(3, StringUtilities::LeftAlign("", Lcd2004::LINE_WIDTH));
}
