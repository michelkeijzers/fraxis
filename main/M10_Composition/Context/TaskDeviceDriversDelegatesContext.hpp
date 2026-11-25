#pragma once

#include <memory>

class PassiveBuzzerTaskDeviceDriversDelegate;

namespace M60::PassiveBuzzer
{
    class PassiveBuzzerTaskDeviceDriversDelegate;
}

namespace M60::I2c
{
    class I2cTaskDeviceDriversDelegate;
}

class TaskDeviceDriversDelegatesContext
{
public:
    /// @brief Do NOT make = default, this causes issues relating to Context class.
    TaskDeviceDriversDelegatesContext();

    TaskDeviceDriversDelegatesContext(
        const TaskDeviceDriversDelegatesContext&) = delete;

    TaskDeviceDriversDelegatesContext& operator=(
        const TaskDeviceDriversDelegatesContext&) = delete;

    TaskDeviceDriversDelegatesContext(
        TaskDeviceDriversDelegatesContext&&) = delete;

    TaskDeviceDriversDelegatesContext& operator=(
        TaskDeviceDriversDelegatesContext&&) = delete;

    /// @brief Do NOT make = default, this causes issues relating to Context class.
    ~TaskDeviceDriversDelegatesContext();

    void Set(
        std::unique_ptr<M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate>
        passiveBuzzerTaskeviceDriversDelegate,
        std::unique_ptr<M60::I2c::I2cTaskDeviceDriversDelegate> i2cTaskDeviceDriversDelegate);
        //std::unique_ptr<I2cTask> i2cTask,
        //std::unique_ptr<SpiTask> spiTask,
        //std::unique_ptr<LedStripsTask> ledStripsTask,
        //std::unique_ptr<DiagnosticsTask> diagnosticsTask,
        //std::unique_ptr<I2sTask> i2sTask,
        //std::unique_ptr<PassiveBuzzerTask> passiveBuzzerTask,
        //std::unique_ptr<SevenSegmentsDisplaysTask> sevenSegmentsDisplaysTask);

    M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate&
        GetPassiveBuzzerTaskDeviceDriversDelegate();

    M60::I2c::I2cTaskDeviceDriversDelegate& GetI2cTaskDeviceDriversDelegate();

    //I2cTask& GetI2cTask();
    //
    //SpiTask& GetSpiTask();
    //
    //LedStripsTask& GetLedStripsTask();
    //
    //DiagnosticsTask& GetDiagnosticsTask();
    //
    //I2sTask& GetI2sTask();

    //PassiveBuzzerTask& GetPassiveBuzzerTask();

    //SevenSegmentsDisplaysTask& GetSevenSegmentsDisplaysTask();

private:
    std::unique_ptr<M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate>
        _passiveBuzzerTaskDeviceDriversDelegate;

    std::unique_ptr<M60::I2c::I2cTaskDeviceDriversDelegate> _i2cTaskDeviceDriversDelegate;

    //
    //std::unique_ptr<I2cTask> _i2cTask;
    //
    //std::unique_ptr<SpiTask> _spiTask;
    //
    //std::unique_ptr<LedStripsTask> _ledStripsTask;
    //
    //std::unique_ptr<DiagnosticsTask> _diagnosticsTask;
    //
    //std::unique_ptr<I2sTask> _i2sTask;

    //std::unique_ptr<PassiveBuzzerTask> _passiveBuzzerTask;

    //std::unique_ptr<SevenSegmentsDisplaysTask> _sevenSegmentsDisplaysTask;
};
