#pragma once 

#include "../L9_Utils/Assert/Assert.hpp"

class Builder;
class Context;

class Orchestrator
{
public:
    Orchestrator(Builder& builder);
    ~Orchestrator();

    void Run();

private:
    Builder& _builder;
    Context* _context;

#ifdef ASSERTS_ENABLED
    void ValidateDeviceSettings();
#endif // ASSERTS_ENABLED

    void CreateLinks();
    void LinkDeviceModelsToDeviceDrivers();
    void InitializeDeviceModels();
    void InitializeDevicesDrivers();
    void InitializeTasks();
    void StartTasks();
};
