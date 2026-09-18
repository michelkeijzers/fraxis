
#include "../Application.hpp"
#include "States.hpp"
#include "Renderer.hpp"
#include "../../../M30_Messages/Types.hpp"
#include <vector>

class ApplicationsManager;

class MenuApplication : public Application
{
public:
    static constexpr char NAME[] = "MENU";
        
    MenuApplication(
        Context& context, 
        ApplicationsManager& applicationsManager);
    
    std::string_view GetName() const override;
    EType GetType() const override;
    std::span<const ETag> GetTags() const override;

    void Start() override;
    void Pause() override;
    void Resume() override;
    void Stop() override;
    void Run() override;

    void OnJoystickDirectionChanged(
        Types::EJoystickId id, 
        Types::EJoystickDirection direction) override;
    void OnJoystickButtonChanged(
        Types::EJoystickId id, bool state) override;
    void OnSystemButtonChanged(
        bool state) override;
    
private:
    ApplicationsManager& _applicationsManager;
    States _states;
    Renderer _renderer;

    void Render(
        bool alwaysRender = false);
};
