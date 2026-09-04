#include "DiagnosticsTask.hpp"
#include "DeviceSettings.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L1_Composition/Context/ServicesContext.hpp"
#include "../L8_Services/Uart/Uart.hpp"
#include "../L9_Utilities/Log/Log.hpp"

DiagnosticsTask::DiagnosticsTask(Context& context) 
:   Task(), 
    _context(context),
    _diagnosticsQueue(_context.GetQueues().GetDiagnosticsQueue()),
    _diagnosticsQueueReader(_diagnosticsQueue, _watchDog, _diagnosticsManager),
    _diagnosticsManager(_context),
    _watchDog(_diagnosticsManager)
{
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
    Log::Entry(Types::ETaskId::DiagnosticsTask, "DiagnosticsTask::Run()");
    while (true)
    {
        while (_diagnosticsQueueReader.HandleMessage())
        {
            // Handle all messages until the queue is empty.
        }

        _watchDog.CheckTimeouts();
        GetRtosTask().DelayTask(1);
    }
    Log::Exit(Types::ETaskId::DiagnosticsTask, "DiagnosticsTask::Run()");
}

/* static */ void DiagnosticsTask::TaskEntry(
    void* param) // NOSONAR: RTOS task entry must use void* by design
{
    auto* self = static_cast<DiagnosticsTask*>(param);
    self->Run();
}
