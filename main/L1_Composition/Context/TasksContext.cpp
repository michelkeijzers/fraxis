#include "../../L8_Services/RtosTask/RtosTask.hpp"

#include "TasksContext.hpp"
#include "../../L2_Applications/ApplicationsTask.hpp"
#include "../../L4_DomainModels/I2c/I2cTask.hpp"
#include "../../L4_DomainModels/LedStrips/LedStripsTask.hpp"

TasksContext::TasksContext() = default;

TasksContext::~TasksContext() = default;

void TasksContext::Set(
    std::unique_ptr<ApplicationsTask> applicationsTask,
    std::unique_ptr<I2cTask> i2cTask,
    std::unique_ptr<LedStripsTask> ledStripsTask)
{
    _applicationsTask = std::move(applicationsTask);
    _i2cTask = std::move(i2cTask);
    _ledStripsTask = std::move(ledStripsTask);
}

void TasksContext::InitializeAll()
{
    _applicationsTask->Initialize();
    _i2cTask->Initialize();
    _ledStripsTask->Initialize();
}

void TasksContext::StartAll()
{
    _applicationsTask->GetRtosTask().Start();
    _i2cTask->GetRtosTask().Start();
    _ledStripsTask->GetRtosTask().Start();
}