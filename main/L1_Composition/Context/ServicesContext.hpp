#pragma once

#include <memory>

// Forward declarations of abstract service interfaces
class Rtos;
class RtosQueue;
class Gpio;
class I2c;
class Rmt;
class Random;

class ServicesContext
{
public:
    ServicesContext();
    ~ServicesContext();

    void Set(
        std::unique_ptr<Rtos> rtos, 
        std::unique_ptr<Gpio> gpio, 
        std::unique_ptr<I2c> i2c, 
        std::unique_ptr<Rmt> rmt,
        std::unique_ptr<Random> random);

    Rtos& GetRtos();    
    Gpio& GetGpio();    
    I2c& GetI2c();  
    Rmt& GetRmt();
    Random& GetRandom();

private:
    std::unique_ptr<Rtos> _rtos;
    std::unique_ptr<Gpio> _gpio;
    std::unique_ptr<I2c> _i2c;
    std::unique_ptr<Rmt> _rmt;
    std::unique_ptr<Random> _random;
};
