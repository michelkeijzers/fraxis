
#include "Applications/ApplicationIds.hpp"
#include "ApplicationsManager.hpp"
#include "ApplicationArena.hpp"
#include "ApplicationsFactory.hpp"
#include "Applications/Send.hpp"
#include "ApplicationsTask.hpp"
#include "Menu/MenuApplication.hpp"
#include "Queues/QueueWriters.hpp"
#include "../M21_Games/Pong.hpp"
#include "../M24_Utilities/AutoRun.hpp"
#include "../M30_Messages/Types.hpp"
#include "../M40_DomainModels/I2c/Displays/Lcd2004/Lcd2004.hpp"
#include "../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../M81_RtosServices/Rtos/Rtos.hpp"
#include "../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../M81_RtosServices/RtosTask/RtosTask.hpp"
#include "../M90_Utilities/Log/Log.hpp"
#include "../M90_Utilities/Assert/Assert.hpp"
#include "../M90_Utilities/String/StringUtilities.hpp"

ApplicationsManager::ApplicationsManager(
    Context& context)
    :
    _context(context),
    _queueWriters(nullptr),
    _nvsSettings(nullptr),
    _ioStates(),
    _menuApplication(_context, *this),
    _applicationArena(),
    _activeApplication(nullptr),
    _activeApplicationId(EApplicationId::Count), // Uninitialized
    _pausedApplication(nullptr),
    _pausedApplicationId(EApplicationId::Count), // Uninitialized
    _destroyFunction(nullptr)
{
}

void ApplicationsManager::Initialize()
{
    _activeApplication = &_menuApplication;
    _activeApplicationId = EApplicationId::Menu;
    _activeApplication->GetSend().SetQueueWriters(*_queueWriters);
    _menuApplication.Start();
}

QueueWriters& ApplicationsManager::GetQueueWriters()
{
     return *_queueWriters; 
}

ApplicationsFactory::Result ApplicationsManager::CreateApplication(
    EApplicationId applicationId)
{
    return ApplicationsFactory::Create(applicationId, _applicationArena, _context, *this);
}

void ApplicationsManager::SetQueueWriters(
    QueueWriters& queueWriters)
{
    _queueWriters = &queueWriters;
}

void ApplicationsManager::SetNvsSettings(
    NvsSettings& nvsSettings)
{
    _nvsSettings = &nvsSettings;
}

void ApplicationsManager::OnJoystickDirectionChanged(
    Types::EJoystickId id, 
    Types::EJoystickDirection direction)
{
    Log::Int(Types::ETaskId::ApplicationsTask, "direction", (uint8_t) direction);
    _ioStates.GetJoystickState(id).SetDirection(direction); 
    _activeApplication->OnJoystickDirectionChanged(id, direction);
}

void ApplicationsManager::OnJoystickButtonChanged(
    Types::EJoystickId id, 
    bool state) 
{
    _ioStates.GetJoystickState(id).SetButtonState(state);
    Assert::IsNotNullptr(
        Types::ETaskId::ApplicationsTask, _activeApplication, "_activeApplication");
    _activeApplication->OnJoystickButtonChanged(id, state);
}

/// @brief  System button always goes to menu application.
/// @param state 
void ApplicationsManager::OnSystemButtonChanged(
    bool state) 
{
    _ioStates.GetSystemButtonState().SetState(state);
    if (_activeApplication != nullptr)
    {
        _activeApplication->OnSystemButtonChanged(state);
    }
}

void ApplicationsManager::Run()
{
    if (_activeApplication != nullptr)
    {
        _activeApplication->Tick();
    }
}

IoStates& ApplicationsManager::GetIoStates() 
{
    return _ioStates; 
}

Application* ApplicationsManager::GetActiveApplication()
{
    return _activeApplication;
}

EApplicationId ApplicationsManager::GetActiveApplicationId()
{
    return _activeApplicationId;
}

void ApplicationsManager::SetActiveApplication(
    Application& application)
{
    _activeApplication = &application;
    _activeApplication->GetSend().SetQueueWriters(*_queueWriters);
}

EApplicationId ApplicationsManager::GetPausedApplicationId()
{
    return _pausedApplicationId;
}

void ApplicationsManager::PauseApplication(
    EApplicationId applicationId)
{
    if (_activeApplication)
    {
        _activeApplication->Pause();
        _pausedApplication = _activeApplication;
        // Optioneel: _activeApplication = _applications[0].get(); (terug naar menu)
    }
}

void ApplicationsManager::ResumeApplication(
    EApplicationId applicationId)
{
    _activeApplication = _pausedApplication;
    _pausedApplication = nullptr;
    _activeApplication->Resume();
}

void ApplicationsManager::StartApplication(
    EApplicationId applicationId)
{
    if (_activeApplication && _destroyFunction)
    {
        _activeApplication->Stop();
        _destroyFunction(_activeApplication);
        _activeApplication = nullptr;
        _destroyFunction = nullptr;
    }
   
    auto result = CreateApplication(applicationId);

    _activeApplication = result.application;
    _destroyFunction = result.destroyFunction;

    if (_activeApplication)
    {
        _activeApplication->Start();
    }

    _pausedApplication = nullptr;
}


void ApplicationsManager::StopApplication(
    EApplicationId applicationId)
{
    if (_activeApplication)
    {
        _activeApplication->Stop();

        if (_destroyFunction)
        {
            _destroyFunction(_activeApplication);
            _destroyFunction = nullptr;
        }

        _activeApplication = nullptr;
    }

    _pausedApplication = nullptr;

    // Systeem-cleanup zoals je in je commentaar had gezet
    DisableTm1637Displays();
    ResetLeds();
    ClearLedStrips();

    // Terugval naar hoofdmenu (bijv. index 0 of menu-app)
     
     StartApplication(EApplicationId::Menu);
     _pausedApplication = nullptr;

     DisableTm1637Displays();
     ResetLeds();
     ClearLedStrips();
}

void ApplicationsManager::DisableTm1637Displays()
{
    Send& send = _activeApplication->GetSend();
    send.Tm1637Enable(Types::ETm1637Id::CentralPanel, false);
    send.Tm1637Enable(Types::ETm1637Id::Player1, false);
    send.Tm1637Enable(Types::ETm1637Id::Player2, false);

    send.Value(Types::ETm1637Id::CentralPanel, 0);
    send.Value(Types::ETm1637Id::Player1, 0);
    send.Value(Types::ETm1637Id::Player2, 0);
}

void ApplicationsManager::ResetLeds()
{
    Send& send = _activeApplication->GetSend();
    send.Led(Types::ELedId::Player1, false);
    send.Led(Types::ELedId::Player2, false);
    send.Led(Types::ELedId::PlayPause, false);
    send.Led(Types::ELedId::Select, false);
    send.Led(Types::ELedId::Setup, false);
}

void ApplicationsManager::ClearLedStrips()
{
    Send& send = _activeApplication->GetSend();
    for (uint8_t x = 0; x < LedStrips::NUMBER_OF_LEDS_PER_LED_STRIP; x++)
    {
        for (uint8_t y = 0; y < LedStrips::NUMBER_OF_LED_STRIPS; y++)
        {
            send.Pixel(x, y, 0, 0, 0);
        }
    }
}

NvsSettings& ApplicationsManager::GetNvsSettings()
{
    Assert::IsNotNullptr(Types::ETaskId::ApplicationsTask, _nvsSettings, "_nvsSettings");
    return *_nvsSettings;
}

void ApplicationsManager::SyncNvsSettings()
{
    Assert::IsNotNullptr(Types::ETaskId::ApplicationsTask, _nvsSettings, "_nvsSettings");
    _nvsSettings->Sync();
}
