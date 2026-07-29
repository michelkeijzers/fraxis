#include "TasksContext.hpp"
#include "../../L0_System/I2cTask.hpp"
#include "../../L2_Applications/ApplicationsTask.hpp"
#include "../../L8_Services/RtosTask/RtosTask.hpp"
#include "../../L0_System/LedStripsTask.hpp"

TasksContext::TasksContext()
{
}

TasksContext::~TasksContext()
{
}

void TasksContext::Set(
    std::unique_ptr<ApplicationsTask> applicationsTask,
    std::unique_ptr<I2cTask> i2cTask,
    std::unique_ptr<LedStripsTask> ledStripsTask)
{
    _applicationsTask = std::move(applicationsTask);
    _i2cTask = std::move(i2cTask);
    _ledStripsTask = std::move(ledStripsTask);
}

ApplicationsTask& TasksContext::GetApplicationsTask() 
{
    return *_applicationsTask; 
}

I2cTask& TasksContext::GetI2cTask() 
{ 
    return *_i2cTask; 
}

LedStripsTask& TasksContext::GetLedStripsTask() 
{
    return *_ledStripsTask; 
}
