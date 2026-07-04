#pragma once

#include "ITimer.hpp"

class Timer
{
public:
    static void Set(ITimer* impl) 
	 {
        instance = impl;
    }

    static uint32_t GetTimeInMs();

private:
    static inline ITimer* instance = nullptr;
};
