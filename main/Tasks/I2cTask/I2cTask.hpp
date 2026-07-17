#pragma once

#include "../../Common/Services/RtosTask/RtosTask.hpp"
#include "../../Core/Components/ComponentsBuilder.hpp"
//#include "../../Common/Components/LedStrip/LedStripsCurrentLimiter.hpp"
#include "../../Common/Services/RTosQueue/RtosQueue.hpp"

class LedStripDriver;

class I2cTask
{
public:
    I2cTask(RtosTask* rtosTask, 
        RtosQueue& i2cQueue, 
        ComponentsBuilder::FraxisComponents& fraxisComponents, 
        ComponentsBuilder::Models& models, 
        ComponentsBuilder::Drivers& drivers);
    void Run();   // main loop
    RtosTask* GetRtosTask() { return _rtosTask; }
    void SetRtosTask(RtosTask* rtosTask);

private:
    RtosTask* _rtosTask;
    RtosQueue& _i2cQueue;
    ComponentsBuilder::FraxisComponents& _fraxisComponents;
    ComponentsBuilder::Models& _models;
    ComponentsBuilder::Drivers& _drivers;
};
