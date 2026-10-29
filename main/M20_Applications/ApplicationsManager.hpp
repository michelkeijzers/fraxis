#pragma once

#include "ApplicationArena.hpp"
#include "ApplicationsFactory.hpp"
#include "IEventListener.hpp"
#include "Applications/ApplicationIds.hpp"
#include "Applications/Application.hpp"
#include "Applications/ApplicationsInfo.hpp"
#include "../M25_Menu/MenuApplication.hpp"
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
        const char* name; // NOSONAR TODO: Store in firmware, same for application type
    };

    explicit ApplicationsManager(
        Context& context);

    ApplicationsManager(const ApplicationsManager&) = delete;
    ApplicationsManager& operator=(const ApplicationsManager&) = delete;
    ApplicationsManager(ApplicationsManager&&) = delete;
    ApplicationsManager& operator=(ApplicationsManager&&) = delete;

    ~ApplicationsManager() override = default;
    
    void Initialize();

    ApplicationsFactory::Result CreateApplication(
        EApplicationId applicationId);

    [[nodiscard]] Send& GetSend();

    QueueWriters& GetQueueWriters();
    void SetQueueWriters(
        QueueWriters& queueWriters);
    
    void SetNvsSettings(
        NvsSettings& nvsSettings);

    void OnJoystickDirectionChanged(
        Types::EJoystickId joystickId, 
        Types::EJoystickDirection direction) override;

    void OnJoystickButtonChanged(
        Types::EJoystickId joystickId, 
        bool state) override;

    void OnSystemButtonChanged(
        bool state) override;
    
    void Run();

    IoStates& GetIoStates();

    Application* GetActiveApplication();
    void SetActiveApplication(
        Application& application);

    [[nodiscard]] bool IsPaused() const;

    void StartApplication(
        EApplicationId applicationId);

    void PauseApplication();

    void ResumeApplication();

    void StopApplication(
        EApplicationId applicationId);

    NvsSettings& GetNvsSettings();

    void SyncNvsSettings();

    MenuApplication* GetMenuApplication();
    
    [[nodiscard]] bool IsMenuApplicationActive() const;

private:
    Context& _context;
    Send _send;
    QueueWriters* _queueWriters = nullptr;
    NvsSettings* _nvsSettings = nullptr;
    IoStates _ioStates;
    MenuApplication _menuApplication;
    ApplicationArena _applicationArena;
    Application* _activeApplication = nullptr;
    bool _isPaused;

    void (*_destroyFunction)(Application*);

    void DisableTm1637Displays();
    void ResetLeds();
    void ClearLedStrips();
};
