#include "WindowsTm1637DeviceDriver.hpp"
#include "Tm1637Model.hpp"
#include <cstdint>
#include <Windows.h>
#include "../../../Windows/GdiSimulator.hpp"

extern SimulatorContext _simulatorContext;

WindowsTm1637DeviceDriver::WindowsTm1637DeviceDriver(Tm1637Model& model)
: Tm1637DeviceDriver(model)
{
}

void WindowsTm1637DeviceDriver::Initialize()
{
}

void WindowsTm1637DeviceDriver::Write()
{
    PostMessage(_simulatorContext.hwndMain, WM_TM1637_UPDATE, 0, 0);
}
