#pragma once

#include "IoStates/IoStates.hpp"
#include "Applications/Application.hpp"

#include <list>
#include <memory>
#include <cstdint>

class Application;
class ApplicationsTask;
class Context;

class ApplicationsManager
{
public:
    ApplicationsManager(ApplicationsTask& applicationsTask, Context& context);
    ~ApplicationsManager();

    void AddApplications();

    IoStates& GetIoStates() { return _ioStates; }

    std::list<std::unique_ptr<Application>>& GetApplications() { return _applications; }

private:
    ApplicationsTask& _applicationsTask;
    Context& _context;
    IoStates _ioStates;
    std::list<std::unique_ptr<Application>> _applications;
};
