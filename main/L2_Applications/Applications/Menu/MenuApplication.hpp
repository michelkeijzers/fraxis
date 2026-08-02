
#include "../Application.hpp"
#include "States.hpp"
#include "Renderer.hpp"
#include "../../../L3_Messages/Types.hpp"

class MenuApplication : public Application
{
public:
    MenuApplication(Context& context, ApplicationsManager& applicationsManager);
    
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Stop() override;
    void Run() override;

    void OnJoystickDirectionChanged(Types::EJoystickId id, Types::EJoystickDirection direction) override;
    void OnJoystickButtonChanged(Types::EJoystickId id, bool state) override;
    void OnSystemButtonChanged(bool state) override;
    
private:
    States _states;
    Renderer _renderer;

    void Render(bool alwaysRender = false);

#ifndef ESP_PLATFORM
    /// @todo Temporary code
    void RunSimulatedDisplay(); 
#endif
};
