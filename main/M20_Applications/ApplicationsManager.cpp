
#include "ApplicationsManager.hpp"
#include "AppArena.hpp"
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
    _appArena(),
    _activeApplication(nullptr),
    _activeApplicationId(Application::EId::Count), // Uninitialized
    _pausedApplication(nullptr),
    _pausedApplicationId(Application::EId::Count) // Uninitialized
{
}

QueueWriters& ApplicationsManager::GetQueueWriters()
{
     return *_queueWriters; 
}

Application* ApplicationsManager::CreateApplication(
    Application::EId id)
{
    //MA
    // switch (id)
    // {
    //     case Application::EId::MenuApplication:
    //         *       _destroyFunction = &DestroyApp<MenuApplication>;
    //     *   &DestroyApp<MenuApplication>;
    //     case Application::EId::Pong:
    //         return new Pong(_context, *this);
    //     case Application::EId::AutoRun:
    //         return new AutoRun(_context, *this);
    //     default:
    //         Assert::Fail(Types::ETaskId::ApplicationsTask, "Unknown app id");
    // }
    return new AutoRun(_context, *this);
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
    Assert::IsNotNullptr(Types::ETaskId::ApplicationsTask, _activeApplication, "_activeApplication");
    _activeApplication->OnJoystickButtonChanged(id, state);
}

/// @brief  System button always goes to menu application.
/// @param state 
void ApplicationsManager::OnSystemButtonChanged(
    bool state) 
{
    //_ioStates.GetSystemButtonState().SetState(state);
    //Assert::IsTrue(Types::ETaskId::ApplicationsTask, _applications.size() > 0, "_applications.size() > 0");
    //_applications[0].get()->OnSystemButtonChanged(state);
}

void ApplicationsManager::Run()
{
    //if (_activeApplication == nullptr)
    //{
    //    Assert::IsNot0(Types::ETaskId::ApplicationsTask, _applications.size(), "_applications.size()");
    //    SetActiveApplication(*_applications[0].get()); // 0 = menu
    //}

    //_activeApplication->Tick();
}

IoStates& ApplicationsManager::GetIoStates() 
{
    return _ioStates; 
}

Application* ApplicationsManager::GetActiveApplication()
{
    return _activeApplication;
}

IApplication::EId ApplicationsManager::GetActiveApplicationId()
{
    return _activeApplicationId;
}

void ApplicationsManager::SetActiveApplication(
    Application& application)
{
    _activeApplication = &application;
}

IApplication::EId ApplicationsManager::GetPausedApplicationId()
{
    return _pausedApplicationId;
}

void ApplicationsManager::PauseApplication(
    IApplication::EId applicationId)
{
    // _activeApplication = _applications[0].get();
    // _pausedApplication = &application;
    // application.Pause();
}

void ApplicationsManager::ResumeApplication(
    IApplication::EId applicationId)
{
    // _activeApplication = _pausedApplication;
    // _pausedApplication = nullptr;
    // application.Resume();
}

void ApplicationsManager::StartApplication(
    Application::EId appId)
{
    // _activeApplication = &application; // TODO Use factory

    // auto result =
    // AppFactory::Create(
    //     id,
    //     _appArena,
    //     _context,
    //     *this);

    // _activeApplication = result.application;
    // _destroyFunction = result.destroyFunction;

    // _activeApplication->Start();

    // _pausedApplication = nullptr;
    // application.Start();
}


void ApplicationsManager::StopApplication(
    IApplication::EId applicationId)
{
    // application.Stop();
    // _destroyFunction(application);

    // _activeApplication = _applications[0].get();
    // _pausedApplication = nullptr;

    // DisableTm1637Displays();
    // ResetLeds();
    // ClearLedStrips();
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
