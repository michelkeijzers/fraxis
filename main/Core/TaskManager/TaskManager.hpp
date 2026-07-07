#pragma once

#include "../Menu/MenuStates.hpp"
#include "../Menu/MenuRenderer.hpp"

class IRtos;
class IRtosQueue;

class LedStrips;
class Lcd1602Display;
class Tm1637;
class PinIo;

class TaskManager
{
public:
    struct Interfaces
    {
        IRtos& rtos;
        IRtosQueue& rtosQueue;

        LedStrips& ledStrips;
        Lcd1602Display& lcdDisplay;
        PinIo& pinIo;
        Tm1637& tm1637CentralPanel;
        Tm1637& tm1637Player1;
        Tm1637& tm1637Player2;
    };

    TaskManager(Interfaces& interfaces);
    void Initialize();
    void Run(bool keepRunning);

private:
    void RunOnce();

private:
    static constexpr uint32_t MENU_UPDATE_INTERVAL_MS = 10;
    static constexpr uint32_t LCD_UPDATE_INTERVAL_MS = 10;
    static constexpr uint32_t MCP23017_UPDATE_INTERVAL_MS = 10;
    static constexpr uint32_t TM1637_UPDATE_INTERVAL_MS = 100;
    static constexpr uint32_t LED_STRIPS_UPDATE_INTERVAL_MS = 16;

    Interfaces _interfaces;

    MenuStates _menuStates;
    MenuRenderer _menuRenderer;

    uint32_t _lastMenuUpdate;
    uint32_t _lastLedStripsUpdate;
    uint32_t _lastMcp23017Update;
    uint32_t _lastLcd1602Update;
    uint32_t _lastTm1637Update;


    void TempSimulate();
};