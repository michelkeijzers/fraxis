
#include "../Application.hpp"

class MenuApplication : public Application
{
public:
    MenuApplication(Context& context, ApplicationsManager& applicationsManager);
    
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Stop() override;
};
