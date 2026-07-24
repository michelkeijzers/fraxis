#pragma once

#include "../../L2_Applications/Task.hpp"

class Context;
class RtosTask;

class I2cTask : public Task
{
public:
    I2cTask(Context& context);
    ~I2cTask();

    void Initialize() override;
    void Run() override;
    static void TaskEntry(void* param);

private:
    Context& _context;
};
