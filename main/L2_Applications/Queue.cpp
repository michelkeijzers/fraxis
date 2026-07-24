#include "Queue.hpp"

Queue::Queue()
{
}

Queue::~Queue() 
{
}

void Queue::SetRtosQueue(RtosQueue& rtosQueue)
{
   _rtosQueue = &rtosQueue;
}
