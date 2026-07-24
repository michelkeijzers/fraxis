#include "ApplicationsManager.hpp"
#include "ApplicationsTask.hpp"

#include "../L8_Services/Rtos/Rtos.hpp"
#include "../L8_Services/RtosQueue/RtosQueue.hpp"
#include "../L8_Services/RtosTask/RtosTask.hpp"
#include "../L8_Services/Debug/Debug.hpp"

ApplicationsManager::ApplicationsManager(Context& context)
: _context(context)
{
}
