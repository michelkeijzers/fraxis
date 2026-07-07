#pragma once

#include "../Menu/MenuInput.hpp"
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
    void Output(const MenuRenderer::Result& result);

private:
    Interfaces _interfaces;

    MenuInput _menuInput;
    MenuStates _menuStates;
    MenuRenderer _menuRenderer;
};