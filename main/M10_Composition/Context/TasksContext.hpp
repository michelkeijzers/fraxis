#pragma once

#include <memory>

class ApplicationsTask;
class I2cTask;
class LedStripsTask;
class DiagnosticsTask;
class NvsTask;

class TasksContext
{
public:
    TasksContext();
    ~TasksContext();

    void Set(
        std::unique_ptr<ApplicationsTask> applicationsTask,
        std::unique_ptr<I2cTask> i2cTask,
        std::unique_ptr<LedStripsTask> ledStripsTask,
        std::unique_ptr<DiagnosticsTask> diagnosticsTask,
        std::unique_ptr<NvsTask> nvsTask = nullptr);

    ApplicationsTask& GetApplicationsTask();
    I2cTask& GetI2cTask();
    LedStripsTask& GetLedStripsTask();
    DiagnosticsTask& GetDiagnosticsTask();
    NvsTask& GetNvsTask();

private:
    std::unique_ptr<ApplicationsTask> _applicationsTask;
    std::unique_ptr<I2cTask> _i2cTask;
    std::unique_ptr<LedStripsTask> _ledStripsTask;
    std::unique_ptr<DiagnosticsTask> _diagnosticsTask;
    std::unique_ptr<NvsTask> _nvsTask;
};
