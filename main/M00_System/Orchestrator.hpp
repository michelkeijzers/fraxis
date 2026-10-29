#pragma once 

#include "../M90_Utilities/Assert/Assert.hpp"

class Builder;
class Context;

class Orchestrator
{
public:
    explicit Orchestrator(
        Builder& builder);

    Orchestrator(const Orchestrator&) = delete;
    Orchestrator& operator=(const Orchestrator&) = delete;
    Orchestrator(Orchestrator&&) = delete;
    Orchestrator& operator=(Orchestrator&&) = delete;
    
    ~Orchestrator() = default;

    void Initialize();
    void StartTasks();

private:
    Builder& _builder;
    Context* _context = nullptr;

#ifdef ASSERTS_ENABLED
    void ValidateDeviceSettings() const;
#endif // ASSERTS_ENABLED

    void CreateLinks();
    void LinkDomainModelsToDeviceModels();
    void LinkDeviceModelsToDeviceDrivers();
    void InitializeServices();
    void LinkDeviceDriversToServices();
    void LinkDeviceDriversToI2cDeviceDrivers();
    void LinkDeviceDriversToSpiDeviceDrivers();
    void LinkDeviceDriversToAudioDeviceDrivers();

    void InitializeDeviceModels();
    void InitializeDevicesDrivers();
    void InitializeTasks();
};
