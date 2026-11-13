#pragma once

#include <memory>

namespace M80
{
    namespace Gpio
    {
        class Gpio;
    }

    namespace I2c
    {
        class I2c;
    }

    namespace I2s
    {
        class I2s;
    }

    namespace Nvs
    {
        class Nvs;
    }

    namespace Pwm
    {
        class Pwm;
    }

    namespace Spi
    {
        class Spi;
    }

    namespace Random
    {
        class Random;
    }

    namespace Rmt
    {
        class Rmt;
    }

    namespace Uart
    {
        class Uart;
    }
}

namespace M81
{
    namespace Rtos
    {
        class Rtos;
    }

    namespace RtosQueue
    {
        class RtosQueue;
    }
}

class ServicesContext
{
public:
    // Do not make = default.
    ServicesContext();
    
    ServicesContext(
        const ServicesContext&) = delete;

    ServicesContext& operator=(
        const ServicesContext&) = delete;

    ServicesContext(
        ServicesContext&&) = delete;

    ServicesContext& operator=(
        ServicesContext&&) = delete;
    
    // Do not make = default.
    ~ServicesContext();

    void SetRtos(
        std::unique_ptr<M81::Rtos::Rtos> rtos);

    void SetGpio(
        std::unique_ptr<M80::Gpio::Gpio> gpio);

    void SetI2c(
        std::unique_ptr<M80::I2c::I2c> i2c);

    void SetSpi(
        std::unique_ptr<M80::Spi::Spi> spi);

    void SetRmt(
        std::unique_ptr<M80::Rmt::Rmt> rmt);

    void SetRandom(
        std::unique_ptr<M80::Random::Random> random);

    void SetUart(
        std::unique_ptr<M80::Uart::Uart> uart);

    void SetNvs(
        std::unique_ptr<M80::Nvs::Nvs> nvs);

    void SetPwm(
        std::unique_ptr<M80::Pwm::Pwm> pwm);

    void SetI2s(
        std::unique_ptr<M80::I2s::I2s> i2s);

    M81::Rtos::Rtos& GetRtos();    

    M80::Gpio::Gpio& GetGpio();    

    M80::I2c::I2c& GetI2c();  

    M80::Spi::Spi& GetSpi();

    M80::Rmt::Rmt& GetRmt();

    M80::Random::Random& GetRandom();

    M80::Uart::Uart& GetUart();

    M80::Nvs::Nvs& GetNvs();

    M80::Pwm::Pwm& GetPwm();

    M80::I2s::I2s& GetI2s();

private:
    std::unique_ptr<M81::Rtos::Rtos> _rtos;

    std::unique_ptr<M80::Gpio::Gpio> _gpio;

    std::unique_ptr<M80::I2c::I2c> _i2c;

    std::unique_ptr<M80::Spi::Spi> _spi;

    std::unique_ptr<M80::Rmt::Rmt> _rmt;

    std::unique_ptr<M80::Random::Random> _random;

    std::unique_ptr<M80::Uart::Uart> _uart;

    std::unique_ptr<M80::Nvs::Nvs> _nvs;

    std::unique_ptr<M80::Pwm::Pwm> _pwm;

    std::unique_ptr<M80::I2s::I2s> _i2s;
};
