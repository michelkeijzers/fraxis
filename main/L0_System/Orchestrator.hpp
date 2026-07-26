#pragma once 

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

    void CreateLinks();
    void LinkDeviceModelsToDeviceDrivers();
    void InitializeDeviceModels();
    void InitializeDevicesDrivers();
    void InitializeTasks();
    void StartTasks();
};
