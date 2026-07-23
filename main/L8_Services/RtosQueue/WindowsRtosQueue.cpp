#include "WindowsRtosQueue.hpp"
#include <chrono>
#include <cstring>

WindowsRtosQueue::WindowsRtosQueue(uint32_t queueLength, uint32_t itemSize)
:   _itemSize(itemSize),
    _maxLength(queueLength)
{}

bool WindowsRtosQueue::Send(const void* itemToQueue, uint32_t ticksToWait)
{
    std::unique_lock<std::mutex> lock(_mtx);

    // If queue is full, wait until space becomes available
    if (_queue.size() >= _maxLength)
    {
        if (!_cv.wait_for(lock,
            std::chrono::milliseconds(ticksToWait),
            [&] { return _queue.size() < _maxLength; }))
        {
            return false; // timeout
        }
    }

    // Copy item bytes into queue
    const uint8_t* src = static_cast<const uint8_t*>(itemToQueue);
    _queue.emplace_back(src, src + _itemSize);

    _cv.notify_one();
    return true;
}

bool WindowsRtosQueue::Receive(void* buffer, uint32_t ticksToWait)
{
    std::unique_lock<std::mutex> lock(_mtx);

    // Wait until queue has data
    if (_queue.empty())
    {
        if (!_cv.wait_for(lock,
            std::chrono::milliseconds(ticksToWait),
            [&] { return !_queue.empty(); }))
        {
            return false; // timeout
        }
    }

    // Pop item
    auto data = std::move(_queue.front());
    _queue.pop_front();

    // Copy into user buffer
    std::memcpy(buffer, data.data(), _itemSize);

    return true;
}


bool WindowsRtosQueue::Peek(void* item, uint32_t timeoutMs)
{
    std::unique_lock<std::mutex> lock(_mtx);

    if (!_cv.wait_for(lock, std::chrono::milliseconds(timeoutMs),
        [&] { return !_queue.empty(); }))
    {
        return false;
    }

    memcpy(item, _queue.front().data(), _itemSize);
    return true;
}

uint32_t WindowsRtosQueue::MessagesWaiting() const
{
    std::lock_guard<std::mutex> lock(_mtx);
    return (uint32_t) _queue.size();
}

uint32_t WindowsRtosQueue::SpacesAvailable() const
{
    std::lock_guard<std::mutex> lock(_mtx);
    return _maxLength - (uint32_t) _queue.size();
}