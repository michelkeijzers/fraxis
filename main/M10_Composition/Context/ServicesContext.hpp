#pragma once

#include <memory>

class Rtos;
class RtosQueue;
class Gpio;
class I2c;
class Spi;
class Rmt;
class Random;
class Uart;
class Nvs;

class ServicesContext
{
public:
    ServicesContext();
    ~ServicesContext();

    void Set(
        std::unique_ptr<Rtos> rtos, 
        std::unique_ptr<Gpio> gpio, 
        std::unique_ptr<I2c> i2c, 
        std::unique_ptr<Spi> spi,
        std::unique_ptr<Rmt> rmt,
        std::unique_ptr<Random> random,
        std::unique_ptr<Uart> uart,
        std::unique_ptr<Nvs> nvs);

    Rtos& GetRtos();    
    Gpio& GetGpio();    
    I2c& GetI2c();  
    Spi& GetSpi();
    Rmt& GetRmt();
    Random& GetRandom();
    Uart& GetUart();
    Nvs& GetNvs();

private:
    std::unique_ptr<Rtos> _rtos;
    std::unique_ptr<Gpio> _gpio;
    std::unique_ptr<I2c> _i2c;
    std::unique_ptr<Spi> _spi;
    std::unique_ptr<Rmt> _rmt;
    std::unique_ptr<Random> _random;
    std::unique_ptr<Uart> _uart;
    std::unique_ptr<Nvs> _nvs;
};
