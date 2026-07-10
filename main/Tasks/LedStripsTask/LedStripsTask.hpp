#pragma once

#include "../../Common/Services/RtosTask/RtosTask.hpp"
#include "../../Core/Components/ComponentsBuilder.hpp"
#include "../../Common/Components/LedStrip/LedStripsCurrentLimiter.hpp"

class LedStripsTask
{
public:
    LedStripsTask(RtosTask* rtosTask,
        ComponentsBuilder::FraxisComponents& fraxisComponents, 
        ComponentsBuilder::Models& models, 
        ComponentsBuilder::Drivers& drivers);
    void Run();   // main loop
    void SetRtosTask(RtosTask* rtosTask);

private:
    static constexpr uint32_t LED_STRIPS_UPDATE_INTERVAL_MS = 16;
    static constexpr uint16_t MAX_LED_STRIPS_CURRENT_MA = 5000;

    RtosTask* _rtosTask;
    ComponentsBuilder::FraxisComponents& _fraxisComponents;
    ComponentsBuilder::Models& _models;
    ComponentsBuilder::Drivers& _drivers;

    LedStripsCurrentLimiter _ledStripsCurrentLimiter;

    uint32_t _lastLedStripsUpdate;
};
