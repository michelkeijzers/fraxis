#include "../../L8_Services/Gpio/Gpio.hpp"
#include "../../L8_Services/I2c/I2c.hpp"
#include "../../L8_Services/Rtos/Rtos.hpp"
#include "../../L8_Services/RtosQueue/RtosQueue.hpp"
#include "../../L8_Services/Random/Random.hpp"

#include "ServicesContext.hpp"

ServicesContext::ServicesContext()
{
}

ServicesContext::~ServicesContext()
{}

void ServicesContext::Set(std::unique_ptr<Rtos> rtos, std::unique_ptr<RtosQueue> queue, std::unique_ptr<Gpio> gpio, 
    std::unique_ptr<I2c> i2c, std::unique_ptr<Random> random)
{
    _rtos = std::move(rtos);
    _queue = std::move(queue);
    _gpio = std::move(gpio);
    _i2c = std::move(i2c);
    _random = std::move(random);
}

Rtos& ServicesContext::GetRtos()
{
    return *_rtos;
}

RtosQueue& ServicesContext::GetQueue()
{
    return *_queue;
}

Gpio& ServicesContext::GetGpio()
{
    return *_gpio;
}

I2c& ServicesContext::GetI2c()
{
    return *_i2c;
}

Random& ServicesContext::GetRandom()
{
    return *_random;
}
