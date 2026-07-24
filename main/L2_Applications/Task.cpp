 #include "Task.hpp"

 Task::Task(RtosTask& rtosTask)
 : _rtosTask(rtosTask) 
 {
 }

 Task::~Task() 
 {
 }

 void SetRtosTask(RtosTask* rtosTask)
 {
    _rtosTask = rtosTask;
 }
