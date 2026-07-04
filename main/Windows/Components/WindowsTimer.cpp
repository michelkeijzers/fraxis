#include <thread>
#include <chrono>
#include "WindowsTimer.hpp"

WindowsTimer::WindowsTimer()
{}

WindowsTimer::~WindowsTimer()
{}

uint32_t WindowsTimer::GetTimeInMs()
{
    using namespace std::chrono;
    return (uint32_t)duration_cast<milliseconds>(
        steady_clock::now().time_since_epoch()
    ).count();
}
