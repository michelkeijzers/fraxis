#include "TaskDeviceDriversDelegatesContext.hpp"
#include "../../M60_DeviceDrivers/I2c/I2cTaskDeviceDriversDelegate.hpp"
#include "../../M60_DeviceDrivers/PassiveBuzzer/PassiveBuzzerTaskDeviceDriversDelegate.hpp"
//#include "../../M00_System/Tasks/I2cTask.hpp"
//#include "../../M00_System/Tasks/SpiTask.hpp"
//#include "../../M00_System/Tasks/LedStripsTask.hpp"
//#include "../../M00_System/Tasks/DiagnosticsTask.hpp"
//#include "../../M00_System/Tasks/I2sTask.hpp"
//#include "../../M00_System/Tasks/PassiveBuzzerTask.hpp"
//#include "../../M00_System/Tasks/SevenSegmentsDisplaysTask.hpp"
//#include "../../M20_Applications/ApplicationsTask.hpp"
//#include "../../M81_RtosServices/RtosTask/RtosTask.hpp"

// Do not make default.
TaskDeviceDriversDelegatesContext::TaskDeviceDriversDelegatesContext()
{
    // No functionality needed.
}

// Do not make default.
TaskDeviceDriversDelegatesContext::~TaskDeviceDriversDelegatesContext() // NOSONAR S3490: no isdefault
{
    // No functionality needed.
}

void TaskDeviceDriversDelegatesContext::Set(
    
    //std::unique_ptr<SpiTask> spiTask,
    //std::unique_ptr<LedStripsTask> ledStripsTask, 
    //std::unique_ptr<DiagnosticsTask> diagnosticsTask,
    //std::unique_ptr<I2sTask> i2sTask,
    //std::unique_ptr<PassiveBuzzerTask> passiveBuzzerTask,
    //std::unique_ptr<SevenSegmentsDisplaysTask> sevenSegmentsDisplaysTask)
    std::unique_ptr<M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate>
        passiveBuzzerTaskDeviceDriversDelegate,
    std::unique_ptr<M60::I2c::I2cTaskDeviceDriversDelegate> i2cTaskDeviceDriversDelegate)
{
    _passiveBuzzerTaskDeviceDriversDelegate = std::move(passiveBuzzerTaskDeviceDriversDelegate);
    _i2cTaskDeviceDriversDelegate = std::move(i2cTaskDeviceDriversDelegate);
    //_applicationsTask = std::move(applicationsTask);
    //_i2cTask = std::move(i2cTask);
    //_spiTask = std::move(spiTask);
    //_ledStripsTask = std::move(ledStripsTask);
    //_diagnosticsTask = std::move(diagnosticsTask);
    //_i2sTask = std::move(i2sTask);
    //_passiveBuzzerTask = std::move(passiveBuzzerTask);
    //_sevenSegmentsDisplaysTask = std::move(sevenSegmentsDisplaysTask);
}

M60::PassiveBuzzer::PassiveBuzzerTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetPassiveBuzzerTaskDeviceDriversDelegate()
{
    return *_passiveBuzzerTaskDeviceDriversDelegate;
}

M60::I2c::I2cTaskDeviceDriversDelegate&
TaskDeviceDriversDelegatesContext::GetI2cTaskDeviceDriversDelegate()
{
    return *_i2cTaskDeviceDriversDelegate;
}

//ApplicationsTask& TasksContext::GetApplicationsTask() 
//{
//    return *_applicationsTask; 
//}
//
//I2cTask& TasksContext::GetI2cTask() 
//{ 
//    return *_i2cTask; 
//}
//
//SpiTask& TasksContext::GetSpiTask() 
//{
//    return *_spiTask; 
//}
//
//LedStripsTask& TasksContext::GetLedStripsTask() 
//{
//    return *_ledStripsTask; 
//}
//
//DiagnosticsTask& TasksContext::GetDiagnosticsTask() 
//{
//    return *_diagnosticsTask; 
//}
//
//I2sTask& TasksContext::GetI2sTask()
//{
//    return *_i2sTask;
//}
//
//PassiveBuzzerTask& TasksContext::GetPassiveBuzzerTask()
//{
//    return *_passiveBuzzerTask;
//}
//
//SevenSegmentsDisplaysTask& TasksContext::GetSevenSegmentsDisplaysTask()
//{
//    return *_sevenSegmentsDisplaysTask;
//}