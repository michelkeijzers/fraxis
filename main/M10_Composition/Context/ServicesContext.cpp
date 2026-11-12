#include "../../M80_Services/Gpio/Gpio.hpp"
#include "../../M80_Services/I2c/I2c.hpp"
#include "../../M80_Services/Spi/Spi.hpp"
#include "../../M80_Services/Rmt/Rmt.hpp"
#include "../../M81_RtosServices/Rtos/Rtos.hpp"
#include "../../M80_Services/Random/Random.hpp"
#include "../../M80_Services/Uart/Uart.hpp"
#include "../../M80_Services/Nvs/Nvs.hpp"
#include "../../M80_Services/Pwm/Pwm.hpp"
#include "../../M80_Services/I2s/I2s.hpp"
#include "../../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "ServicesContext.hpp"

ServicesContext::ServicesContext()
:
    _rtos(nullptr),
    _gpio(nullptr),
    _i2c(nullptr),
    _spi(nullptr),
    _rmt(nullptr),
    _random(nullptr),
    _uart(nullptr),
    _nvs(nullptr),
    _pwm(nullptr),
    _i2s(nullptr)
{
}

ServicesContext::~ServicesContext() // NOSONAR S3490: no isdefault 
{
    // No actions needed. Do not make = default.
}

void ServicesContext::Set( // NOSONAR S107: >= 7 parameters
    std::unique_ptr<M81::Rtos::Rtos> rtos, 
    std::unique_ptr<M80::Gpio::Gpio> gpio,
    std::unique_ptr<M80::I2c::I2c> i2c, 
    std::unique_ptr<M80::Spi::Spi> spi,
    std::unique_ptr<M80::Rmt::Rmt> rmt,
    std::unique_ptr<M80::Random::Random> random,
    std::unique_ptr<M80::Uart::Uart> uart,
    std::unique_ptr<M80::Nvs::Nvs> nvs,
    std::unique_ptr<M80::Pwm::Pwm> pwm,
    std::unique_ptr<M80::I2s::I2s> i2s)
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

M81::Rtos::Rtos& ServicesContext::GetRtos()
{
    return *_rtos;
}

M80::Gpio::Gpio& ServicesContext::GetGpio()
{
    return *_gpio;
}

M80::I2c::I2c& ServicesContext::GetI2c()
{
    return *_i2c;
}

M80::Spi::Spi& ServicesContext::GetSpi()
{
    return *_spi;
}

M80::Rmt::Rmt& ServicesContext::GetRmt()
{
    return *_rmt;
}

M80::Random::Random& ServicesContext::GetRandom()
{
    return *_random;
}

M80::Uart::Uart& ServicesContext::GetUart()
{
    return *_uart;
}

M80::Nvs::Nvs& ServicesContext::GetNvs()
{
    return *_nvs;
}

M80::Pwm::Pwm& ServicesContext::GetPwm()
{
    return *_pwm;
}

M80::I2s::I2s& ServicesContext::GetI2s()
{
    return *_i2s;
}
