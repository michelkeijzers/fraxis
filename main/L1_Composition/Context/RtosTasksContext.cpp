#include "../../L8_Services/RtosTask/RtosTask.hpp"

#include "RtosTasksContext.hpp"
#include "../../L2_Applications/ApplicationsTask.hpp"
#include "../../L4_DomainModels/Tasks/I2cTask.hpp"
#include "../../L4_DomainModels/Tasks/LedStripsTask.hpp"

RtosTasksContext::RtosTasksContext() = default;

RtosTasksContext::~RtosTasksContext() = default;

void RtosTasksContext::Set(
    std::unique_ptr<ApplicationsTask> applicationsTask,
    std::unique_ptr<I2cTask> i2cTask,
    std::unique_ptr<LedStripsTask> ledStripsTask)
{
    _applicationsTask = std::move(applicationsTask);
    _i2cTask = std::move(i2cTask);
    _ledStripsTask = std::move(ledStripsTask);
}
