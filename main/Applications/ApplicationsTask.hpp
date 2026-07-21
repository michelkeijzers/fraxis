#pragma once

#include "../Common/Services/RtosTask/RtosTask.hpp"
#include "../Core/Menu/MenuStates.hpp"
#include "../Core/Menu/MenuRenderer.hpp"
#include "../Core/Components/ComponentsBuilder.hpp"


class RtosTask;
class RtosQueue;

class ApplicationsTask
{
public:
    ApplicationsTask(RtosTask* rtosTask, RtosQueue* ledStripQueue, RtosQueue* i2cQueue,
        ComponentsBuilder::FraxisComponents& fraxisComponents, 
        ComponentsBuilder::Models& models,
        ComponentsBuilder::Drivers& drivers);

    void Run();   // main loop
    RtosTask* GetRtosTask() { return _rtosTask; }
    void SetRtosTask(RtosTask* rtosTask);

private:
    static constexpr uint32_t MENU_UPDATE_INTERVAL_MS = 10;
    static constexpr uint32_t LCD_UPDATE_INTERVAL_MS = 10;
    static constexpr uint32_t MCP23017_UPDATE_INTERVAL_MS = 10;
    static constexpr uint32_t TM1637_UPDATE_INTERVAL_MS = 100;

    void TempSimulate(uint32_t now);

    RtosTask* _rtosTask;

    RtosQueue* _ledStripQueue;
    RtosQueue* _i2cQueue;

    ComponentsBuilder::FraxisComponents& _fraxisComponents;
    ComponentsBuilder::Models& _models;
    ComponentsBuilder::Drivers& _drivers;

    MenuStates _menuStates;
    MenuRenderer _menuRenderer;

    uint32_t _lastMenuUpdate;

    uint32_t _lastMcp23017Update;
    uint32_t _lastLcd1602Update;
    uint32_t _lastTm1637Update;
};
