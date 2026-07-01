#pragma once
class IRtos 
{
public:
    virtual ~IRtos() = default;
    virtual void vTaskDelay(int ms) = 0;
};
