#pragma once

#include "../../L8_Services/RtosTask/RtosTask.hpp"

class Context;

class I2cTask
{
public:
    I2cTask(Context& context);
    ~I2cTask();

private:
    Context& _context;
};
