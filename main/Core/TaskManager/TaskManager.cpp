#include "TaskManager.hpp"
#include "../Services/IRtos.hpp"
#include "../Services/IRtosQueue.hpp"
#include "../Components/LedStrips.hpp"
#include "../Components/Lcd1602Display.hpp"
#include "../Components/PinIo.hpp"
#include "../Components/Tm1637.hpp"

//TODO: Temp
uint32_t todo2500 = 25;
uint32_t todo4800 = 0;
uint32_t todo2323 = 1000;


TaskManager::TaskManager(Interfaces& interfaces)
: _interfaces(interfaces), _menuInput(interfaces.pinIo), _menuStates(), _menuRenderer(_menuStates)
{
}

void TaskManager::Initialize()
{
    _interfaces.ledStrips.Initialize();
    _interfaces.lcdDisplay.Initialize();
    _interfaces.pinIo.Initialize();
	_interfaces.tm1637CentralPanel.Initialize();
	_interfaces.tm1637Player1.Initialize();
    _interfaces.tm1637Player2.Initialize();
}

void TaskManager::Run(bool keepRunning)
{
    if (keepRunning)
    {
        while (true)
        {
            RunOnce();
        }
    }
    else
    {
        RunOnce();
    }
}

void TaskManager::RunOnce()
{
    MenuRenderer::Result result = _menuRenderer.Render();
    Output(result);
    EInput in = _menuInput.ReadInput();
	_menuStates.Update(in);

    //TODO: TEMP 
    static uint32_t index = 0;
    index = (index + 1) % 360;
    static uint32_t color = 0;
    color = (color + 5) % 255;

    _interfaces.ledStrips.SetPixel(index,
        color % 256,
        (color + 50) % 256,
        (color + 100) % 256);

    _interfaces.tm1637CentralPanel.SetTime(todo2323 / 60, todo2323 % 60);
    todo2323--;

    _interfaces.tm1637Player1.SetValue(todo2500);
    todo2500 += 97;
    _interfaces.tm1637Player2.SetValue(todo4800);
    todo4800 += 1;

    _interfaces.pinIo.SetPauseLed(todo4800 % 100 < 50); 
    _interfaces.pinIo.SetSelectLed(todo4800 % 100 > 30);
    _interfaces.pinIo.SetSetupLed(todo4800 % 100 > 20);
    _interfaces.pinIo.SetPlayer1Led(todo4800 % 500 > 20);
    _interfaces.pinIo.SetPlayer2Led(todo4800 % 200 > 50);

    // END TEMP

    _interfaces.rtos.DelayTask(10);
    {
    }
}

void TaskManager::Output(const MenuRenderer::Result& result) 
 {
    if (_menuStates.forceRender) 
    {
	// 	 DebugPrint("+----------------+\n");
	// 	 std::string line1 = "|" + std::string(result.line1.data(), 16) + "|\n";
	// 	 DebugPrint(line1.c_str());
	// 	 std::string line2 = "|" + std::string(result.line2.data(), 16) + "|\n";
	// 	 DebugPrint(line2.c_str());
    //    DebugPrint("+----------------+\n");

        _interfaces.ledStrips.Update();
		_interfaces.lcdDisplay.WriteLines(result.line1.data(), result.line2.data());
		_interfaces.lcdDisplay.Update();
		_interfaces.tm1637CentralPanel.SetTime(0, 0);
	    _interfaces.tm1637Player1.SetValue(0);
        _interfaces.tm1637Player2.SetValue(0);
		_menuStates.forceRender = false;
    }
}
