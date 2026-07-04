#include "Rtos.hpp"

void Rtos::TaskDelay(int ms)
{
    if (instance)
    {
        instance->TaskDelay(ms);
    }
}
