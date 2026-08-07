#pragma once

#include "IApplication.hpp"
#include "../IEventListener.hpp"
#include "Send.hpp"

class Context;
class ApplicationsManager;

class Application : public IApplication, public IEventListener
{
public:
    Application(
        Context& context, 
        ApplicationsManager& applicationsManager);
    virtual ~Application() = default;

    enum class EId 
    {
        Menu, 
        Pong
    };

    enum class EType 
    {
        Game,
        Demo,
        Tool,
        Utility,
        Last
    };
    
    Context& GetContext();
    ApplicationsManager& GetApplicationsManager();

private:
    Context& _context;
    ApplicationsManager& _applicationsManager;

protected:
    Send& GetSend();

private: 
    // To be defined after _applicationsManager because of -w ordering
    Send _send;
};
