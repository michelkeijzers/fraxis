#include "Queue.hpp"

Queue::Queue()
:   _rtosQueue(nullptr)
{
}

void Queue::SetRtosQueue(
	RtosQueue& rtosQueue)
{
   _rtosQueue = &rtosQueue;
}

RtosQueue& Queue::GetRtosQueue() 
{
   return *_rtosQueue; 
}
