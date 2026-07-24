#pragma once

#include "IEventListener.hpp"
#include "Applications/Application.hpp"
#include "IoStates/IoStates.hpp"
#include <vector>
#include <memory>
#include <cstdint>

class Application;
class ApplicationsTask;
class Context;

class ApplicationsManager : IEventListener
{
public:
    ApplicationsManager(ApplicationsTask& applicationsTask, Context& context);
    ~ApplicationsManager();

    void AddApplications();

    void OnJoystickDirectionChanged(IoStates::EJoystickId id, JoystickState::EDirection direction) override;
    void OnJoystickButtonChanged(IoStates::EJoystickId id, bool state) override;
    void OnSystemButtonChanged(bool state) override;

    IoStates& GetIoStates() { return _ioStates; }

    std::vector<std::unique_ptr<Application>>& GetApplications() { return _applications; }

    uint16_t GetActiveApplicationIndex();
    Application& GetActiveApplication();
    void SetActiveApplicationIndex(uint16_t applicationIndex);
    uint16_t GetResumedApplicationIndex();
    void SetResumedApplicationIndex(uint16_t applicationIndex);
    
private:
    ApplicationsTask& _applicationsTask;
    Context& _context;
    IoStates _ioStates;
    std::vector<std::unique_ptr<Application>> _applications;
    uint16_t _activeApplicationIndex;
    uint16_t _resumedApplicationIndex;
};
