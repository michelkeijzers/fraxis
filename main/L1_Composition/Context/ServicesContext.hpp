#pragma once

#include <memory>

// Forward declarations of abstract service interfaces
class Rtos;
class RtosQueue;
class Gpio;
class I2c;
class Random;

class ServicesContext
{
public:
    ServicesContext();
    ~ServicesContext();

    void Set(std::unique_ptr<Rtos> rtos, std::unique_ptr<RtosQueue> queue, std::unique_ptr<Gpio> gpio, 
        std::unique_ptr<I2c> i2c, std::unique_ptr<Random> random);

    Rtos& GetRtos();    
    RtosQueue& GetQueue();
    Gpio& GetGpio();    
    I2c& GetI2c();  
    Random& GetRandom();

private:
    std::unique_ptr<Rtos> _rtos;
    std::unique_ptr<RtosQueue> _queue;
    std::unique_ptr<Gpio> _gpio;
    std::unique_ptr<I2c> _i2c;
    std::unique_ptr<Random> _random;
};
