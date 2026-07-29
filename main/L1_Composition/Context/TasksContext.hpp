#pragma once

#include <memory>

// Forward declarations of domain models
class ApplicationsTask;
class I2cTask;
class LedStripsTask;

class TasksContext
{
public:
    TasksContext();
    ~TasksContext();

    void Set(
        std::unique_ptr<ApplicationsTask> applicationsTask,
        std::unique_ptr<I2cTask> i2cTask,
        std::unique_ptr<LedStripsTask> ledStripsTask);

    ApplicationsTask& GetApplicationsTask();
    I2cTask& GetI2cTask();
    LedStripsTask& GetLedStripsTask();

private:
    std::unique_ptr<ApplicationsTask> _applicationsTask;
    std::unique_ptr<I2cTask> _i2cTask;
    std::unique_ptr<LedStripsTask> _ledStripsTask;
};
