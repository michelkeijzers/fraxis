#pragma once

#include <memory>

// Forward declarations of domain models
class ApplicationsTask;
class I2cTask;
class LedStripsTask;

class RtosTasksContext
{
public:
    RtosTasksContext();
    ~RtosTasksContext();

    void Set(
        std::unique_ptr<ApplicationsTask> applicationsTask,
        std::unique_ptr<I2cTask> i2cTask,
        std::unique_ptr<LedStripsTask> ledStripsTask);

    void InitializeAll();
    void StartAll();

    ApplicationsTask& GetApplicationsTask() { return *_applicationsTask; }
    I2cTask& GetI2cTask() { return *_i2cTask; }
    LedStripsTask& GetLedStripsTask() { return *_ledStripsTask; }

private:
    std::unique_ptr<ApplicationsTask> _applicationsTask;
    std::unique_ptr<I2cTask> _i2cTask;
    std::unique_ptr<LedStripsTask> _ledStripsTask;
};
