#include "MenuSimulator.hpp"
#include "MenuRenderer.hpp"
#include "MenuInput.hpp"
#include <iostream>
#include "../Components/Lcd1602Display.hpp"

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
//#include "DebugPrint.hpp"
#endif


MenuSimulator::MenuSimulator( Lcd1602Display& lcdDisplay)
    : _renderer(_menuStates), 
    _lcdDisplay(lcdDisplay)
{
}

void MenuSimulator::SetJoystickState(AtariJoystick::EId joystickId, uint8_t pressedItems)
{
	_input.SetJoystickState(joystickId, pressedItems);
}	

void MenuSimulator::SetSystemButtonState(bool pressed)
{
	_input.SetSystemButtonState(pressed);
}

void MenuSimulator::run() {
    //while (true) 
    {
        MenuRenderer::Result result = _renderer.Render();
        Output(result);
        EInput in = _input.readInput();
		  printf("in = %d\n", (int)in);
        _menuStates.Update(in);
        //Sleep(100);
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
		 _menuStates.forceRender = false;
    }
}

