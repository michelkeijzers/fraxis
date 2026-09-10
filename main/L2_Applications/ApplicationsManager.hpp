#pragma once

#include "IEventListener.hpp"
#include "Applications/Application.hpp"
#include "../L3_Messages/Types.hpp"
#include "../L4_DomainModels/I2c/IoPins/Joystick.hpp"
#include <vector>
#include <memory>
#include <cstdint>

class Application;
class ApplicationsTask;
class Context;
class QueueWriters;

class ApplicationsManager : IEventListener
{
public:
    explicit ApplicationsManager(
        Context& context);
    ~ApplicationsManager() = default;
    
    QueueWriters& GetQueueWriters();
    void SetQueueWriters(
        QueueWriters& queueWriters);

    void AddApplications();

    void OnJoystickDirectionChanged(
        Types::EJoystickId id, 
        Types::EJoystickDirection direction) override;
    void OnJoystickButtonChanged(
        Types::EJoystickId id, 
        bool state) override;
    void OnSystemButtonChanged(
        bool state) override;
    
    void Run();

    IoStates& GetIoStates();

    const std::vector<std::unique_ptr<Application>>& GetApplications() const;

    Application& GetActiveApplication();
    void SetActiveApplication(
        Application& application);
    Application& GetPausedApplication();
    void StartApplication(
        Application& application);
    void PauseApplication(
        Application& application);
    void ResumeApplication(
        Application& application);
    void StopApplication(
        Application& application);

private:
    Context& _context;
    QueueWriters* _queueWriters;
    IoStates _ioStates;
    std::vector<std::unique_ptr<Application>> _applications;
    Application* _activeApplication;
    Application* _pausedApplication;

    void DisableTm1637Displays();
    void ResetLeds();
    void ClearLedStrips();
};
