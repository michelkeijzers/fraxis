#include "WindowsRtos.hpp"
#include "windows.h"

WindowsRtos::WindowsRtos()
{}

WindowsRtos::~WindowsRtos()
{}

void WindowsRtos::vTaskDelay(int ms)
{
	Sleep(10);
}