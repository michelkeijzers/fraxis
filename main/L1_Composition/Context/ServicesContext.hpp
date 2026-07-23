#pragma once

#include <memory>

// Forward declarations of abstract service interfaces
class Rtos;
class RtosQueue;
class Random;

class ServicesContext
{
public:
    ServicesContext();
    ~ServicesContext();

    void Set(std::unique_ptr<Rtos> rtos, std::unique_ptr<RtosQueue> queue, std::unique_ptr<Random> random);

    Rtos& GetRtos()            { return *_rtos; }
    RtosQueue& GetQueue()      { return *_queue; }
    Random& GetRandom()        { return *_random; }

private:
    std::unique_ptr<Rtos> _rtos;
    std::unique_ptr<RtosQueue> _queue;
    std::unique_ptr<Random> _random;
};
