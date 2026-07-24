#include "../../Application.hpp"

class AutoRun : public Application
{
public:
    AutoRun(Context& context, ApplicationsManager& applicationsManager);
    
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Stop() override;

    void OnJoystickDirectionChanged(IoStates::EJoystickId id, JoystickState::EDirection direction) override;
    void OnJoystickButtonChanged(IoStates::EJoystickId id, bool state) override;
    void OnSystemButtonChanged(bool state) override;
};

