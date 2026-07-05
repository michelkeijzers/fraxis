#include "MenuSimulator.hpp"
#include "MenuRenderer.hpp"
#include "MenuInput.hpp"
#include <iostream>
#include "../Services/IRtos.hpp"
#include "../Services/IRtosQueue.hpp"
#include "../Components/Lcd1602Display.hpp"
#include "../Components/PinIo.hpp"
#include "../Components/Tm1637.hpp"

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
//#include "DebugPrint.hpp"
#endif

uint32_t todo2500 = 25;
uint32_t todo4800 = 0;
uint32_t todo2323 = 1000;


MenuSimulator::MenuSimulator(IRtos& rtos, IRtosQueue& rtosQueue,
    Lcd1602Display& lcdDisplay, PinIo& pinIo, 
	Tm1637& tm1637CentralPanel, Tm1637& tm1637Player1, Tm1637& tm1637Player2)
    : _rtos(rtos), _rtosQueue(rtosQueue),
    _lcdDisplay(lcdDisplay), _pinIo(pinIo), 
	_tm1637CentralPanel(tm1637CentralPanel), _tm1637Player1(tm1637Player1), _tm1637Player2(tm1637Player2),
    _menuInput(pinIo), _renderer(_menuStates)
{
}

void MenuSimulator::Initialize()
{
    _lcdDisplay.Initialize();
    _pinIo.Initialize();
	 _tm1637CentralPanel.Initialize();
	 _tm1637Player1.Initialize();
    _tm1637Player2.Initialize();
}

void MenuSimulator::run() {
    //while (true) 
    {
        MenuRenderer::Result result = _renderer.Render();
        Output(result);
        EInput in = _menuInput.ReadInput();
		  printf("in = %d\n", (int)in);
        _menuStates.Update(in);

        //TODO: TEMP 
        _tm1637CentralPanel.SetTime(todo2323 / 60, todo2323 % 60);
        todo2323--;

        _tm1637Player1.SetValue(todo2500);
        todo2500 += 97;
        _tm1637Player2.SetValue(todo4800);
        todo4800 += 1;

        _pinIo.SetPauseLed(todo4800 % 100 < 50); 
        _pinIo.SetSelectLed(todo4800 % 100 > 30);
        _pinIo.SetSetupLed(todo4800 % 100 > 20);
        _pinIo.SetPlayer1Led(todo4800 % 500 > 20);
        _pinIo.SetPlayer2Led(todo4800 % 200 > 50);

        // END TEMP

        _rtos.DelayTask(10);
    }
}

 void MenuSimulator::Output(const MenuRenderer::Result& result) {
    if (_menuStates.forceRender) 
    {
	// 	 DebugPrint("+----------------+\n");
	// 	 std::string line1 = "|" + std::string(result.line1.data(), 16) + "|\n";
	// 	 DebugPrint(line1.c_str());
	// 	 std::string line2 = "|" + std::string(result.line2.data(), 16) + "|\n";
	// 	 DebugPrint(line2.c_str());
    //    DebugPrint("+----------------+\n");

		 _lcdDisplay.WriteLines(result.line1.data(), result.line2.data());
		 _lcdDisplay.Update();
		 _tm1637CentralPanel.SetTime(0, 0);
		 _tm1637Player1.SetValue(0);
       _tm1637Player2.SetValue(0);
		 _menuStates.forceRender = false;
    }
}

