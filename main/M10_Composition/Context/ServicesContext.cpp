#include "../../M80_Services/Gpio/Gpio.hpp"
#include "../../M80_Services/I2c/I2c.hpp"
#include "../../M80_Services/Spi/Spi.hpp"
#include "../../M80_Services/Rmt/Rmt.hpp"
#include "../../M81_RtosServices/Rtos/Rtos.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../../M80_Services/Random/Random.hpp"
#include "../../M80_Services/Uart/Uart.hpp"
#include "../../M80_Services/Nvs/Nvs.hpp"
#include "../../M80_Services/Pwm/Pwm.hpp"
#include "../../M80_Services/I2s/I2s.hpp"
#include "ServicesContext.hpp"

ServicesContext::ServicesContext()
{
}

ServicesContext::~ServicesContext()
{
}

void ServicesContext::Set(
    std::unique_ptr<Rtos> rtos, 
    std::unique_ptr<Gpio> gpio, 
    std::unique_ptr<I2c> i2c, 
    std::unique_ptr<Spi> spi,
    std::unique_ptr<Rmt> rmt,
    std::unique_ptr<Random> random,
    std::unique_ptr<Uart> uart,
    std::unique_ptr<Nvs> nvs,
    std::unique_ptr<Pwm> pwm,
    std::unique_ptr<I2s> i2s)
{
    _rtos = std::move(rtos);
    _gpio = std::move(gpio);
    _i2c = std::move(i2c);
    _spi = std::move(spi);
    _rmt = std::move(rmt);
    _random = std::move(random);
    _uart = std::move(uart);
    _nvs = std::move(nvs);
    _pwm = std::move(pwm);
    _i2s = std::move(i2s);
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

Spi& ServicesContext::GetSpi()
{
    return *_spi;
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

Nvs& ServicesContext::GetNvs()
{
    return *_nvs;
}

Pwm& ServicesContext::GetPwm()
{
    return *_pwm;
}

I2s& ServicesContext::GetI2s()
{
    return *_i2s;
}
