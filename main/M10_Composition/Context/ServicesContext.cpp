#include "../../M80_Services/Gpio/Gpio.hpp"
#include "../../M80_Services/I2c/I2c.hpp"
#include "../../M80_Services/Rmt/Rmt.hpp"
#include "../../M80_Services/Rtos/Rtos.hpp"
#include "../../M80_Services/RtosQueue/RtosQueue.hpp"
#include "../../M80_Services/Random/Random.hpp"
#include "../../M80_Services/Uart/Uart.hpp"
#include "ServicesContext.hpp"

ServicesContext::ServicesContext()
{
}

ServicesContext::~ServicesContext()
{}

void ServicesContext::Set(
    std::unique_ptr<Rtos> rtos, 
    std::unique_ptr<Gpio> gpio, 
    std::unique_ptr<I2c> i2c, 
    std::unique_ptr<Rmt> rmt, 
    std::unique_ptr<Random> random,
    std::unique_ptr<Uart> uart)
{
    _rtos = std::move(rtos);
    _gpio = std::move(gpio);
    _i2c = std::move(i2c);
    _rmt = std::move(rmt);
    _random = std::move(random);
    _uart = std::move(uart);
}

Rtos& ServicesContext::GetRtos()
{
    return *_rtos;
}

Gpio& ServicesContext::GetGpio()
{
    return *_gpio;
}

I2c& ServicesContext::GetI2c()
{
    return *_i2c;
}

Rmt& ServicesContext::GetRmt()
{
    return *_rmt;
}

Random& ServicesContext::GetRandom()
{
    return *_random;
}

Uart& ServicesContext::GetUart()
{
    return *_uart;
}
