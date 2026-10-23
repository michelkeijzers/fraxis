#pragma once

#include "ApplicationArena.hpp"
#include "ApplicationsFactory.hpp"
#include "IEventListener.hpp"
#include "Menu/MenuApplication.hpp"
#include "Applications/ApplicationIds.hpp"
#include "Applications/Application.hpp"
#include "Applications/ApplicationsInfo.hpp"
#include "../M30_Messages/Types.hpp"
#include "../M40_DomainModels/I2c/IoPins/Joystick.hpp"
#include <vector>
#include <memory>
#include <cstdint>

class ApplicationArena;
class Application;
class ApplicationsInfo;
class ApplicationsTask;
class Context;
class QueueWriters;
class NvsSettings;

class ApplicationsManager : public IEventListener
{
public:
    struct ApplicationInfo
    {
        EApplicationId id;
        const char* name; // TODO: Store in firmware, same for application type.
    };

    explicit ApplicationsManager(
        Context& context);
    ~ApplicationsManager() = default;
    
    void Initialize();

    ApplicationsFactory::Result CreateApplication(
        EApplicationId applicationId);

    QueueWriters& GetQueueWriters();
    void SetQueueWriters(
        QueueWriters& queueWriters);
    void SetNvsSettings(
        NvsSettings& nvsSettings);

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

    Application* GetActiveApplication();
    EApplicationId GetActiveApplicationId();
    void SetActiveApplication(
        Application& application);
    EApplicationId GetPausedApplicationId();
    void StartApplication(
        EApplicationId applicationId);
    void PauseApplication(
        EApplicationId applicationId);
    void ResumeApplication(
        EApplicationId applicationId);
    void StopApplication(
        EApplicationId applicationId);

    NvsSettings& GetNvsSettings();
    void SyncNvsSettings();

private:
    Context& _context;
    QueueWriters* _queueWriters;
    NvsSettings* _nvsSettings;
    IoStates _ioStates;
    MenuApplication _menuApplication;
    ApplicationArena _applicationArena;
    Application* _activeApplication;
    EApplicationId _activeApplicationId;
    Application* _pausedApplication;
    EApplicationId _pausedApplicationId;

    void (*_destroyFunction)(Application*);

    void DisableTm1637Displays();
    void ResetLeds();
    void ClearLedStrips();
};
