#include "Queue.hpp"
#include "../M81_RtosServices/RtosQueue/IRtosQueue.hpp"

Queue::Queue()
:   _rtosQueue(nullptr)
{
}

void Queue::SetRtosQueue(
    M81::RtosQueue::IRtosQueue& rtosQueue)
{
   _rtosQueue = &rtosQueue;
}

M81::RtosQueue::IRtosQueue& Queue::GetRtosQueue() 
{
   return *_rtosQueue; 
}
