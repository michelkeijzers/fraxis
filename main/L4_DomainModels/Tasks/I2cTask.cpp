#include "I2cTask.hpp"

I2cTask::I2cTask(Context& context) 
: Task(), _context(context)
{
}

I2cTask::~I2cTask() 
{
}

void I2cTask::Initialize()
{
}

void I2cTask::Run()
{
}

/* static */ void I2cTask::TaskEntry(void* param)
{
    auto* self = static_cast<I2cTask*>(param);
    self->Run();
}