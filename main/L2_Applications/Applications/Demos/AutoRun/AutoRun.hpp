#include "../../Application.hpp"

class AutoRun : public Application
{
public:
    AutoRun(Context& context, ApplicationsManager& applicationsManager);
    
    void Start() override;
    void Pause() override;
    void Resume() override;
    void Stop() override;
};

