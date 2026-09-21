#include "TasksContext.hpp"
#include "../../M00_System/I2cTask.hpp"
#include "../../M00_System/LedStripsTask.hpp"
#include "../../M00_System/DiagnosticsTask.hpp"
#include "../../M00_System/NvsTask.hpp"
#include "../../M20_Applications/ApplicationsTask.hpp"
#include "../../M80_Services/RtosTask/RtosTask.hpp"

TasksContext::TasksContext()
{
}

TasksContext::~TasksContext()
{
}

void TasksContext::Set(
    std::unique_ptr<ApplicationsTask> applicationsTask,
    std::unique_ptr<I2cTask> i2cTask,
    std::unique_ptr<LedStripsTask> ledStripsTask, 
    std::unique_ptr<DiagnosticsTask> diagnosticsTask,
    std::unique_ptr<NvsTask> nvsTask)
{
    _applicationsTask = std::move(applicationsTask);
    _i2cTask = std::move(i2cTask);
    _ledStripsTask = std::move(ledStripsTask);
    _diagnosticsTask = std::move(diagnosticsTask);
    _nvsTask = std::move(nvsTask);
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

DiagnosticsTask& TasksContext::GetDiagnosticsTask() 
{
    return *_diagnosticsTask; 
}

NvsTask& TasksContext::GetNvsTask() 
{
    return *_nvsTask; 
}
