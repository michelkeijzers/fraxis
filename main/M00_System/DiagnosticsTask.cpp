#include "DiagnosticsTask.hpp"
#include "DeviceSettings.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M10_Composition/Context/ServicesContext.hpp"
#include "../M80_Services/Uart/IUart.hpp"
#include "../M90_Utilities/Assert/IAssert.hpp"
#include "../M90_Utilities/Log/Log.hpp"

DiagnosticsTask::DiagnosticsTask(
    Context& context,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities,
    M90::Time::ITimeUtilities& timeUtilities)
:   
    Task(log),
    _context(context),
    _diagnosticsQueue(_context.GetQueues().GetDiagnosticsQueue()),
    _diagnosticsQueueReader(
        _diagnosticsQueue, 
        _watchDog, 
        _diagnosticsManager, 
        assert, 
        stringUtilities),
    _diagnosticsManager(_context, assert, stringUtilities),
    _watchDog(_diagnosticsManager, timeUtilities)
{
    // No actions required.
}

void DiagnosticsTask::Initialize()
{
    _context.GetServices().GetUart().Initialize(
        DeviceSettings::UART_BAUD_RATE,
        DeviceSettings::UART_RX_BUFFER_SIZE,
        DeviceSettings::UART_TX_BUFFER_SIZE);
}

void DiagnosticsTask::Run()
{
    GetLog().Entry(Types::ETaskId::DiagnosticsTask, "DiagnosticsTask::Run()");
    while (true)
    {
        while (_diagnosticsQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _watchDog.CheckTimeouts();
        GetRtosTask().DelayTask(1);
    }
    GetLog().Exit(Types::ETaskId::DiagnosticsTask, "DiagnosticsTask::Run()");
}

/* static */ void DiagnosticsTask::TaskEntry(
    void* param) // NOSONAR: RTOS task entry must use void* by design
{
    auto* self = static_cast<DiagnosticsTask*>(param);
    self->Run();
}
