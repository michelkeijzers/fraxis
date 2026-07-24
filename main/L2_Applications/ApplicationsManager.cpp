#include "ApplicationsManager.hpp"
#include "ApplicationsTask.hpp"

#include "Applications/Menu/MenuApplication.hpp"
#include "Applications/Demos/AutoRun/AutoRun.hpp"

#include "../L8_Services/Rtos/Rtos.hpp"
#include "../L8_Services/RtosQueue/RtosQueue.hpp"
#include "../L8_Services/RtosTask/RtosTask.hpp"
#include "../L8_Services/Debug/Debug.hpp"

ApplicationsManager::ApplicationsManager(ApplicationsTask& applicationsTask, Context& context)
: _applicationsTask(applicationsTask), _context(context), _ioStates(), _applications()
{
}

ApplicationsManager::~ApplicationsManager()
{
}

void ApplicationsManager::AddApplications()
{
    MenuApplication menuApplication(_context, *this);
    _applications.push_back(std::make_unique<MenuApplication>(_context, *this));

    AutoRun autoRun(_context, *this);
    _applications.push_back(std::make_unique<AutoRun>(_context, *this));
}
