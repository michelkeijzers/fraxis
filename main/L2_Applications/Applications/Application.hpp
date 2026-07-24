#pragma once

#include "IApplication.hpp"

class Context;
class ApplicationsManager;

class Application : IApplication
{
public:
    Application(Context& context, ApplicationsManager& applicationsManager);
    virtual ~Application();

    enum class EId 
    {
        Menu, 
        Pong
    };

    enum class EType 
    {
        Menu,
        Game,
        Demo,
        Tool,
        Utility
    };
    
    Context& GetContext() { return _context; }
    ApplicationsManager& GetApplicationsManager() { return _applicationsManager; }


private:
    Context& _context;
    ApplicationsManager& _applicationsManager;
};
