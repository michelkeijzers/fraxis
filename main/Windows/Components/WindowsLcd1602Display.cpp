#include "WindowsLcd1602Display.hpp"
#include <cstring>

WindowsLcd1602Display::WindowsLcd1602Display() 
{
}

void WindowsLcd1602Display::WriteLines(const char* line1, const char* line2)
{
	memcpy(_line1, line1, 16);
	memcpy(_line2, line2, 16);
}

//void WindowsLcd1602Display::Update()
//{
//}
