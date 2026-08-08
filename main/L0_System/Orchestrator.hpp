#pragma once 

#include "../L9_Utilities/Assert/Assert.hpp"

class Builder;
class Context;

class Orchestrator
{
public:
    explicit Orchestrator(
        Builder& builder);
    ~Orchestrator() = default;

    void Initialize();
    void StartTasks();

private:
    Builder& _builder;
    Context* _context;

#ifdef ASSERTS_ENABLED
    void ValidateDeviceSettings() const;
#endif // ASSERTS_ENABLED

    void CreateLinks();
    void LinkDomainModelsToInternalComponents();
    void LinkDomainModelsToDeviceModels();
    void LinkDeviceModelsToDeviceDrivers();
    void LinkDeviceDriversToServices();
    void LinkDeviceDriversToI2cDeviceDrivers();

    void InitializeDeviceModels();
    void InitializeDevicesDrivers();
    void InitializeTasks();
};
