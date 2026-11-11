#include "Queue.hpp"
#include "../M81_RtosServices/RtosQueue/RtosQueue.hpp"

Queue::Queue()
:   _rtosQueue(nullptr)
{
}

void Queue::SetRtosQueue(
    M81::RtosQueue::RtosQueue& rtosQueue)
{
   _rtosQueue = &rtosQueue;
}

M81::RtosQueue::RtosQueue& Queue::GetRtosQueue() 
{
   return *_rtosQueue; 
}
