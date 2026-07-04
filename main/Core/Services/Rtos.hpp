#pragma once

#include "IRtos.hpp"

class Rtos
{
public:
    static void Set(IRtos* impl) 
	 {
        instance = impl;
    }

    static void TaskDelay(int ms);


private:
    static inline IRtos* instance = nullptr;
};
