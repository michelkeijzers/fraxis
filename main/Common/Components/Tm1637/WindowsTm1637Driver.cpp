#include "WindowsTm1637Driver.hpp"
#include "Tm1637Model.hpp"
#include <cstdint>
#include <Windows.h>
#include "../../../Windows/GdiSimulator.hpp"

extern SimulatorContext _simulatorContext;

WindowsTm1637Driver::WindowsTm1637Driver(Tm1637Model& model)
: Tm1637Driver(model)
{
}

void WindowsTm1637Driver::Initialize()
{
}

void WindowsTm1637Driver::Write()
{
    PostMessage(_simulatorContext.hwndMain, WM_TM1637_UPDATE, 0, 0);
}
