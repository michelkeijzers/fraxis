#pragma once

#include <memory>

class ApplicationsTask;
class I2cTask;
class SpiTask;
class LedStripsTask;
class DiagnosticsTask;
class I2sTask;

class TasksContext
{
public:
    /// @brief Do NOT make = default, this causes issues relating to Context class.
    TasksContext();

    TasksContext(const TasksContext&) = delete;
    TasksContext& operator=(const TasksContext&) = delete;
    TasksContext(TasksContext&&) = delete;
    TasksContext& operator=(TasksContext&&) = delete;

    /// @brief Do NOT make = default, this causes issues relating to Context class.
    ~TasksContext();

    void Set(
        std::unique_ptr<ApplicationsTask> applicationsTask,
        std::unique_ptr<I2cTask> i2cTask,
        std::unique_ptr<SpiTask> spiTask,
        std::unique_ptr<LedStripsTask> ledStripsTask,
        std::unique_ptr<DiagnosticsTask> diagnosticsTask,
        std::unique_ptr<I2sTask> i2sTask);

    ApplicationsTask& GetApplicationsTask();
    I2cTask& GetI2cTask();
    SpiTask& GetSpiTask();
    LedStripsTask& GetLedStripsTask();
    DiagnosticsTask& GetDiagnosticsTask();
    I2sTask& GetI2sTask();

private:
    std::unique_ptr<ApplicationsTask> _applicationsTask;
    std::unique_ptr<I2cTask> _i2cTask;
    std::unique_ptr<SpiTask> _spiTask;
    std::unique_ptr<LedStripsTask> _ledStripsTask;
    std::unique_ptr<DiagnosticsTask> _diagnosticsTask;
    std::unique_ptr<I2sTask> _i2sTask;
};
