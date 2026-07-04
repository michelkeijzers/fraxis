#pragma once

class IRtos 
{
public:
    virtual ~IRtos() = default;

    virtual void TaskDelay(int ms) = 0;
};
