#include "../../M80_Services/Gpio/IGpio.hpp"
#include "../../M80_Services/I2c/I2c.hpp"
#include "../../M80_Services/Spi/Spi.hpp"
#include "../../M80_Services/Rmt/Rmt.hpp"
#include "../../M81_RtosServices/Rtos/Rtos.hpp"
#include "../../M80_Services/Random/IRandom.hpp"
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

void ServicesContext::SetRtos(
    std::unique_ptr<M81::Rtos::IRtos> rtos)
{
    _rtos = std::move(rtos);
}

void ServicesContext::SetGpio(
    std::unique_ptr<M80::Gpio::IGpio> gpio)
{
    _gpio = std::move(gpio);
}

void ServicesContext::SetI2c(
    std::unique_ptr<M80::I2c::I2c> i2c)
{
    _i2c = std::move(i2c);
}

void ServicesContext::SetSpi(
    std::unique_ptr<M80::Spi::Spi> spi)
{
    _spi = std::move(spi);
}

void ServicesContext::SetRmt(
    std::unique_ptr<M80::Rmt::Rmt> rmt)
{
    _rmt = std::move(rmt);
}

void ServicesContext::SetRandom(
    std::unique_ptr<M80::Random::IRandom> random)
{
    _random = std::move(random);
}

void ServicesContext::SetUart(
    std::unique_ptr<M80::Uart::Uart> uart)
{
    _uart = std::move(uart);
}

void ServicesContext::SetNvs(
    std::unique_ptr<M80::Nvs::Nvs> nvs)
{
    _nvs = std::move(nvs);
}

void ServicesContext::SetPwm(
    std::unique_ptr<M80::Pwm::Pwm> pwm)
{
    _pwm = std::move(pwm);
}

void ServicesContext::SetI2s(
    std::unique_ptr<M80::I2s::I2s> i2s)
{
    _i2s = std::move(i2s);
}

M81::Rtos::IRtos& ServicesContext::GetRtos()
{
    return *_rtos;
}

M80::Gpio::IGpio& ServicesContext::GetGpio()
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

M80::Random::IRandom& ServicesContext::GetRandom()
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
