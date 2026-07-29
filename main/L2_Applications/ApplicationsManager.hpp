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
    ApplicationsManager(ApplicationsTask& applicationsTask, Context& context);
    ~ApplicationsManager();
    
    QueueWriters& GetQueueWriters();
    void SetQueueWriters(QueueWriters& queueWriters);

    void AddApplications();

    void OnJoystickDirectionChanged(Types::EJoystickId id, Types::EJoystickDirection direction) override;
    void OnJoystickButtonChanged(Types::EJoystickId id, bool state) override;
    void OnSystemButtonChanged(bool state) override;
    
    void Run();

    IoStates& GetIoStates();

    std::vector<std::unique_ptr<Application>>& GetApplications();

    uint16_t GetActiveApplicationIndex();
    Application& GetActiveApplication();
    void SetActiveApplicationIndex(uint16_t applicationIndex);
    uint16_t GetResumedApplicationIndex();
    void SetResumedApplicationIndex(uint16_t applicationIndex);
    
private:
    ApplicationsTask& _applicationsTask;
    Context& _context;
    QueueWriters* _queueWriters;
    IoStates _ioStates;
    std::vector<std::unique_ptr<Application>> _applications;
    uint16_t _activeApplicationIndex;
    uint16_t _resumedApplicationIndex;
};
