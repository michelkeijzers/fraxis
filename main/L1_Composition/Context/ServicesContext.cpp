#include "../../L8_Services/Gpio/Gpio.hpp"
#include "../../L8_Services/I2c/I2c.hpp"
#include "../../L8_Services/Rmt/Rmt.hpp"
#include "../../L8_Services/Rtos/Rtos.hpp"
#include "../../L8_Services/RtosQueue/RtosQueue.hpp"
#include "../../L8_Services/Random/Random.hpp"
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
    std::unique_ptr<Random> random)
{
    _rtos = std::move(rtos);
    _gpio = std::move(gpio);
    _i2c = std::move(i2c);
    _rmt = std::move(rmt);
    _random = std::move(random);
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
