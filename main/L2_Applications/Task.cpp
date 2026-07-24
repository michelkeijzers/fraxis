 #include "Task.hpp"

 Task::Task()
 {
 }

 Task::~Task() 
 {
 }

 void Task::SetRtosTask(RtosTask& rtosTask)
 {
    _rtosTask = &rtosTask;
 }
