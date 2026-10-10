#pragma once

#include <memory>

class ApplicationsTask;
class I2cTask;
class SpiTask;
class LedStripsTask;
class DiagnosticsTask;
class AudioTask;

class TasksContext
{
public:
    TasksContext();
    ~TasksContext();

    void Set(
        std::unique_ptr<ApplicationsTask> applicationsTask,
        std::unique_ptr<I2cTask> i2cTask,
        std::unique_ptr<SpiTask> spiTask,
        std::unique_ptr<LedStripsTask> ledStripsTask,
        std::unique_ptr<DiagnosticsTask> diagnosticsTask,
        std::unique_ptr<AudioTask> audioTask);

    ApplicationsTask& GetApplicationsTask();
    I2cTask& GetI2cTask();
    SpiTask& GetSpiTask();
    LedStripsTask& GetLedStripsTask();
    DiagnosticsTask& GetDiagnosticsTask();
    AudioTask& GetAudioTask();

private:
    std::unique_ptr<ApplicationsTask> _applicationsTask;
    std::unique_ptr<I2cTask> _i2cTask;
    std::unique_ptr<SpiTask> _spiTask;
    std::unique_ptr<LedStripsTask> _ledStripsTask;
    std::unique_ptr<DiagnosticsTask> _diagnosticsTask;
    std::unique_ptr<AudioTask> _audioTask;
};
