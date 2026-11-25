#pragma once

#include <memory>

class WatchDog;
class DiagnosticsManager;

class SystemContext
{
public:
    SystemContext();

    SystemContext(
        const SystemContext&) = delete;

    SystemContext& operator=(
        const SystemContext&) = delete;

    SystemContext(
        SystemContext&&) = delete;

    SystemContext& operator=(
        SystemContext&&) = delete;

    ~SystemContext();

    void Set(
        std::unique_ptr<WatchDog> watchDog,
        std::unique_ptr<DiagnosticsManager> diagnosticsManager);

    WatchDog& GetWatchDog();

    DiagnosticsManager& GetDiagnosticsManager();

private:
    std::unique_ptr<WatchDog> _watchDog;

    std::unique_ptr<DiagnosticsManager> _diagnosticsManager;
};
