#pragma once

#include "../../Core/Services/IRtosQueue.hpp"
#include <mutex>
#include <condition_variable>
#include <deque>
#include <vector>

class WindowsRtosQueue : public IRtosQueue
{
public:
	WindowsRtosQueue(uint32_t queueLength, uint32_t itemSize);
	~WindowsRtosQueue() = default;

    bool Send(const void* itemToQueue, uint32_t ticksToWait) override;
    bool Receive(void* buffer, uint32_t ticksToWait) override;

private:
    std::mutex _mtx;
    std::condition_variable _cv;
    std::deque<std::vector<uint8_t>> _queue;
    uint32_t _itemSize;
    uint32_t _maxLength;
};
