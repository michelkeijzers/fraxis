#pragma once

#include "../Components/ComponentsBuilder.hpp"
#include <memory>
#include <cstdint>

class IRtosTask;
class IRtosQueue;

class LedStrips;
class Lcd1602Display;
class Tm1637;
class PinIo;

class SystemTask;
class LedStripsTask;

class TaskManager
{
public:
    TaskManager(ComponentsBuilder::FraxisComponents& fraxisComponents, ComponentsBuilder::Models& models, 
        ComponentsBuilder::Drivers& componentsBuilder);
    void Initialize();
    void Run(bool keepRunning);

private:
    void RunOnce();

private:
    void CreateTasks();
    static void SystemTaskFunction(void* param);
    static void LedStripsTaskFunction(void* param);
        
    ComponentsBuilder::FraxisComponents& _fraxisComponents;
    ComponentsBuilder::Models& _models;
    ComponentsBuilder::Drivers& _drivers;

    SystemTask* _systemTask;
    LedStripsTask* _ledStripsTask;
};