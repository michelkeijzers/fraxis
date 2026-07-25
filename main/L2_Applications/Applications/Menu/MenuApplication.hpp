
#include "../Application.hpp"
#include "../../IoStates/IoStates.hpp"
#include "States.hpp"
#include "Renderer.hpp"
#include "../../../L4_DomainModels/I2c/IoPins/Joystick.hpp"

class MenuApplication : public Application
{
public:
    MenuApplication(Context& context, ApplicationsManager& applicationsManager);
    
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Stop() override;
    void Run() override;

    void OnJoystickDirectionChanged(IoStates::EJoystickId id, Joystick::EDirection direction) override;
    void OnJoystickButtonChanged(IoStates::EJoystickId id, bool state) override;
    void OnSystemButtonChanged(bool state) override;
    
private:
    States _states;
    Renderer _renderer;

    void Render();
};
