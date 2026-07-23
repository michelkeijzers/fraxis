#pragma once

//#include "../../L2_Applications/ComponentsBuilder/ComponentsBuilder.hpp"
#include "../../L8_Services/RtosTask/RtosTask.hpp"
#include "../../L8_Services/RTosQueue/RtosQueue.hpp"

#include "../../Common/Components/LedStrip/LedStripsCurrentLimiter.hpp"

class LedStripDriver;

class LedStripsTask
{
public:
    // LedStripsTask(RtosTask* rtosTask, 
    //     RtosQueue& ledStripsQueue, 
    //     ComponentsBuilder::FraxisComponents& fraxisComponents, 
    //     ComponentsBuilder::Models& models, 
    //     ComponentsBuilder::Drivers& drivers);
    void Run();   // main loop
    // RtosTask* GetRtosTask() { return _rtosTask; }
    // void SetRtosTask(RtosTask* rtosTask);

private:
    static constexpr uint32_t LED_STRIPS_UPDATE_INTERVAL_MS = 16;
    static constexpr uint16_t MAX_LED_STRIPS_CURRENT_MA = 5000;

    // RtosTask* _rtosTask;
    // RtosQueue& _ledStripsQueue;
    // ComponentsBuilder::FraxisComponents& _fraxisComponents;
    // ComponentsBuilder::Models& _models;
    // ComponentsBuilder::Drivers& _drivers;

    LedStripsCurrentLimiter _ledStripsCurrentLimiter;
};
