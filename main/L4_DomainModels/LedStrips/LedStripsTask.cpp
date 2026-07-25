#include "LedStripsTask.hpp"

LedStripsTask::LedStripsTask(Context& context) 
: Task(), _context(context)
{
}

LedStripsTask::~LedStripsTask() 
{
}

void LedStripsTask::Initialize()
{
}

void LedStripsTask::Run()
{
}

/* static */ void LedStripsTask::TaskEntry(void* param)
{
    auto* self = static_cast<LedStripsTask*>(param);
    self->Run();
}
