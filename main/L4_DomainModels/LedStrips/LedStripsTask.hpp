#pragma once

#include "../../L2_Applications/Task.hpp"

class RtosTask;
class Context;

class LedStripsTask : public Task
{
public:
    LedStripsTask(Context& context);
    ~LedStripsTask();
    
    void Initialize() override;
    void Run() override;
    static void TaskEntry(void* param);

private:
    Context& _context;
};
