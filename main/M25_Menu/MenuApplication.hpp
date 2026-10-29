#pragma once

#include "States/States.hpp"
#include "Renderer/Renderer.hpp"
#include "../M20_Applications/Applications/Application.hpp"
#include "../M30_Messages/Types.hpp"
#include <vector>
#include <array>

class ApplicationsManager;

class MenuApplication : public Application
{
public:
#ifdef __INTELLISENSE__
#pragma diag_suppress 28
#endif
    static const std::array<char, 5> NAME;

    MenuApplication(
        Context& context, 
        ApplicationsManager& applicationsManager);

    void Start() override;
    void Pause() override;
    void Resume() override;
    void Stop() override;
    void Tick() override;

    void OnJoystickDirectionChanged(
        Types::EJoystickId joystickId, 
        Types::EJoystickDirection direction) override;
        
    void OnJoystickButtonChanged(
        Types::EJoystickId joystickId, 
        bool state) override;

    void OnSystemButtonChanged(
        bool state) override;
    
    States& GetStates();
    
private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
    ApplicationsManager& _applicationsManager;
    States _states;
    Renderer _renderer;

    void Render(
        bool alwaysRender = false);
};
