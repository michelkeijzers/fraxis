#pragma once

#include "../Components/ComponentsBuilder.hpp"
#include <memory>
#include <cstdint>

class IRtosTask;
class RtosQueue;

class LedStrips;
class Lcd1602Display;
class Tm1637;
class PinIo;

class SystemTask;
class LedStripsTask;
class I2cTask;

class LedStripDriver;

class TaskManager
{
public:
    TaskManager(ComponentsBuilder::FraxisComponents& fraxisComponents, 
        ComponentsBuilder::Models& models, 
        ComponentsBuilder::Drivers& componentsBuilder);
    void Initialize();
    void Run(bool keepRunning);

private:
    void RunOnce();

private:
    void CreateTasks();
    void CreateQueues();
    void StartTasks();

    static void SystemTaskFunction(void* param);
    static void LedStripsTaskFunction(void* param);
    static void I2cTaskFunction(void* param);
        
    ComponentsBuilder::FraxisComponents& _fraxisComponents;
    ComponentsBuilder::Models& _models;
    ComponentsBuilder::Drivers& _drivers;

    SystemTask* _systemTask;
    LedStripsTask* _ledStripsTask;
    I2cTask* _i2cTask;

    RtosQueue* _systemQueue;
    RtosQueue* _ledStripsQueue;
    RtosQueue* _i2cQueue;
};