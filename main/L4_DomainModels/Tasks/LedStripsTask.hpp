#pragma once

#include "../../L8_Services/RtosTask/RtosTask.hpp"

class Context;

class LedStripsTask
{
public:
    LedStripsTask(Context& context);
    ~LedStripsTask();

private:
    Context& _context;
};
