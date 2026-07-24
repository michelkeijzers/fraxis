#pragma once

#include "Task.hpp"
#include "ApplicationsManager.hpp"

#include "../L8_Services/RtosTask/RtosTask.hpp"

class Context;
class ApplicationsManager;
class LedStripsQueue;
class InputQueue;
class OutputQueue;

class ApplicationsTask : public Task
{
public:
    ApplicationsTask(Context& context);
    ~ApplicationsTask();

    void Initialize() override;
    void Run() override;
    static void TaskEntry(void* param);

private:
    Context& _context;
    ApplicationsManager _applicationsManager;

    LedStripsQueue& _ledStripsQueue;
    InputQueue& _inputQueue;
    OutputQueue& _outputQueue;
    

//     static constexpr uint32_t MENU_UPDATE_INTERVAL_MS = 10;
//     static constexpr uint32_t LCD_UPDATE_INTERVAL_MS = 10;
//     static constexpr uint32_t MCP23017_UPDATE_INTERVAL_MS = 10;
//     static constexpr uint32_t TM1637_UPDATE_INTERVAL_MS = 100;

//     void TempSimulate(uint32_t now);


//     MenuStates _menuStates;
//     MenuRenderer _menuRenderer;

//     uint32_t _lastMenuUpdate;

//     uint32_t _lastMcp23017Update;
//     uint32_t _lastLcd1602Update;
//     uint32_t _lastTm1637Update;
};
