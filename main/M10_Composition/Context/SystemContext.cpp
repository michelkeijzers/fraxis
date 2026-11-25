#include "SystemContext.hpp"
#include "../../M00_System/WatchDog.hpp"
#include "../../M00_System/DiagnosticsManager.hpp"

SystemContext::SystemContext()
:
    _watchDog(nullptr),
    _diagnosticsManager(nullptr)
{
    // No functionality required.
}

SystemContext::~SystemContext() = default;

void SystemContext::Set(
    std::unique_ptr<WatchDog> watchDog,
    std::unique_ptr<DiagnosticsManager> diagnosticsManager)
{
    _watchDog = std::move(watchDog);
    _diagnosticsManager = std::move(diagnosticsManager);
}

WatchDog& SystemContext::GetWatchDog()
{
    return *_watchDog; 
}

DiagnosticsManager& SystemContext::GetDiagnosticsManager()
{
    return *_diagnosticsManager;
}
