#include "Application.hpp"

Application::Application(Context& context, ApplicationsManager& applicationsManager) 
: _context(context), _applicationsManager(applicationsManager)
{
}

Application::~Application() 
{
}
