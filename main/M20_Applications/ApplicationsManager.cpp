
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
    _send(),
    _queueWriters(nullptr),
    _nvsSettings(nullptr),
    _ioStates(),
    _menuApplication(_context, *this),
    _applicationArena(),
    _activeApplication(nullptr),
    _isPaused(false),
    _destroyFunction(nullptr)
{
}

void ApplicationsManager::Initialize()
{
    _send.SetQueueWriters(GetQueueWriters());
    _menuApplication.Start();
}

Send& ApplicationsManager::GetSend()
{
    return _send;
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
    if ((_activeApplication == nullptr) || _isPaused)
    {
        _menuApplication.OnJoystickDirectionChanged(id, direction);
    }
    else
    {
        Assert::IsNotNullptr(
            Types::ETaskId::ApplicationsTask, _activeApplication, "_activeApplication");
        _activeApplication->OnJoystickDirectionChanged(id, direction);
    }
}

void ApplicationsManager::OnJoystickButtonChanged(
    Types::EJoystickId id, 
    bool state) 
{
    _ioStates.GetJoystickState(id).SetButtonState(state);
    if ((_activeApplication == nullptr) || _isPaused)
    {
        _menuApplication.OnJoystickButtonChanged(id, state);
    }
    else
    {
        Assert::IsNotNullptr(
            Types::ETaskId::ApplicationsTask, _activeApplication, "_activeApplication");
        _activeApplication->OnJoystickButtonChanged(id, state);
    }
}

/// @brief  System button always goes to menu application.
/// @param state 
void ApplicationsManager::OnSystemButtonChanged(
    bool state) 
{
    _ioStates.GetSystemButtonState().SetState(state);
    _menuApplication.OnSystemButtonChanged(state);
}

void ApplicationsManager::Run()
{
    if (_activeApplication == nullptr)
    {
        _menuApplication.Tick();
    }
    else
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

void ApplicationsManager::SetActiveApplication(
    Application& application)
{
    _activeApplication = &application;
    _activeApplication->GetSend().SetQueueWriters(*_queueWriters);
}

bool ApplicationsManager::IsPaused()
{
    return _isPaused;
}

void ApplicationsManager::PauseApplication()
{
    if (_activeApplication)
    {
        _activeApplication->Pause();
        _isPaused = true;
    }
}

void ApplicationsManager::ResumeApplication()
{
    _isPaused = false;
    _activeApplication->Resume();
}

void ApplicationsManager::StartApplication(
    EApplicationId applicationId)
{
    if (applicationId != EApplicationId::Menu)
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
    }

    if (_activeApplication)
    {
        _activeApplication->Start();
    }

    _isPaused = false;
}


void ApplicationsManager::StopApplication(
    EApplicationId applicationId)
{
    if (applicationId != EApplicationId::Menu)
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
    }

    _isPaused = false;

    // Systeem-cleanup zoals je in je commentaar had gezet
    DisableTm1637Displays();
    ResetLeds();
    ClearLedStrips();

    // Terugval naar hoofdmenu (bijv. index 0 of menu-app)
     
     StartApplication(EApplicationId::Menu);

     DisableTm1637Displays();
     ResetLeds();
     ClearLedStrips();
}

/// @brief Disabled TM1637 displays. Always called by menu application.
void ApplicationsManager::DisableTm1637Displays()
{
    Send& send = _menuApplication.GetSend();
    send.Tm1637Enable(Types::ETm1637Id::CentralPanel, false);
    send.Tm1637Enable(Types::ETm1637Id::Player1, false);
    send.Tm1637Enable(Types::ETm1637Id::Player2, false);

    send.Value(Types::ETm1637Id::CentralPanel, 0);
    send.Value(Types::ETm1637Id::Player1, 0);
    send.Value(Types::ETm1637Id::Player2, 0);
}

/// @brief Resets leds (not from LED strips). Always called by menu application.
void ApplicationsManager::ResetLeds()
{
    Send& send = _menuApplication.GetSend();
    send.Led(Types::ELedId::Player1, false);
    send.Led(Types::ELedId::Player2, false);
    send.Led(Types::ELedId::PlayPause, false);
    send.Led(Types::ELedId::Select, false);
    send.Led(Types::ELedId::Setup, false);
}

/// @brief Clears LED strips. Always called by menu application.
void ApplicationsManager::ClearLedStrips()
{
    Send& send = _menuApplication.GetSend();
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

MenuApplication* ApplicationsManager::GetMenuApplication()
{
    return &_menuApplication;
}

bool ApplicationsManager::IsMenuApplicationActive() const
{
    return _activeApplication == &_menuApplication;
}
