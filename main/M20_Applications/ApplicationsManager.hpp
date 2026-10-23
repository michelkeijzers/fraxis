#pragma once

#include "AppArena.hpp"
#include "IEventListener.hpp"
#include "Applications/ApplicationIds.hpp"
#include "Applications/Application.hpp"
#include "Applications/ApplicationsInfo.hpp"
#include "Applications/ApplicationIds.hpp"
#include "../M30_Messages/Types.hpp"
#include "../M40_DomainModels/I2c/IoPins/Joystick.hpp"
#include <vector>
#include <memory>
#include <cstdint>

class AppArena;
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
        const char* name; // TODO: Store in firmware, same for app type.
    };

    explicit ApplicationsManager(
        Context& context);
    ~ApplicationsManager() = default;
    
    Application* CreateApplication(
        EApplicationId id);

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
        EApplicationId appId);
    void PauseApplication(
        EApplicationId appId);
    void ResumeApplication(
        EApplicationId appId);
    void StopApplication(
        EApplicationId appId);

    NvsSettings& GetNvsSettings();
    void SyncNvsSettings();

private:
    Context& _context;
    QueueWriters* _queueWriters;
    NvsSettings* _nvsSettings;
    IoStates _ioStates;
    AppArena _appArena;
    Application* _activeApplication;
    EApplicationId _activeApplicationId;
    Application* _pausedApplication;
    EApplicationId _pausedApplicationId;

    void DisableTm1637Displays();
    void ResetLeds();
    void ClearLedStrips();
};
