#pragma once

#include <memory>

namespace M80
{
    namespace Gpio
    {
        class IGpio;
    }

    namespace I2c
    {
        class II2c;
    }

    namespace I2s
    {
        class II2s;
    }

    namespace Nvs
    {
        class INvs;
    }

    namespace Pwm
    {
        class IPwm;
    }

    namespace Spi
    {
        class ISpi;
    }

    namespace Random
    {
        class IRandom;
    }

    namespace Rmt
    {
        class IRmt;
    }

    namespace Uart
    {
        class IUart;
    }
}

namespace M81
{
    namespace Rtos
    {
        class IRtos;
    }

    namespace RtosQueue
    {
        class IRtosQueue;
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
        std::unique_ptr<M81::Rtos::IRtos> rtos);

    void SetGpio(
        std::unique_ptr<M80::Gpio::IGpio> gpio);

    void SetI2c(
        std::unique_ptr<M80::I2c::II2c> i2c);

    void SetSpi(
        std::unique_ptr<M80::Spi::ISpi> spi);

    void SetRmt(
        std::unique_ptr<M80::Rmt::IRmt> rmt);

    void SetRandom(
        std::unique_ptr<M80::Random::IRandom> random);

    void SetUart(
        std::unique_ptr<M80::Uart::IUart> uart);

    void SetNvs(
        std::unique_ptr<M80::Nvs::INvs> nvs);

    void SetPwm(
        std::unique_ptr<M80::Pwm::IPwm> pwm);

    void SetI2s(
        std::unique_ptr<M80::I2s::II2s> i2s);

    M81::Rtos::IRtos& GetRtos();    

    M80::Gpio::IGpio& GetGpio();    

    M80::I2c::II2c& GetI2c();  

    M80::Spi::ISpi& GetSpi();

    M80::Rmt::IRmt& GetRmt();

    M80::Random::IRandom& GetRandom();

    M80::Uart::IUart& GetUart();

    M80::Nvs::INvs& GetNvs();

    M80::Pwm::IPwm& GetPwm();

    M80::I2s::II2s& GetI2s();

private:
    std::unique_ptr<M81::Rtos::IRtos> _rtos;

    std::unique_ptr<M80::Gpio::IGpio> _gpio;

    std::unique_ptr<M80::I2c::II2c> _i2c;

    std::unique_ptr<M80::Spi::ISpi> _spi;

    std::unique_ptr<M80::Rmt::IRmt> _rmt;

    std::unique_ptr<M80::Random::IRandom> _random;

    std::unique_ptr<M80::Uart::IUart> _uart;

    std::unique_ptr<M80::Nvs::INvs> _nvs;

    std::unique_ptr<M80::Pwm::IPwm> _pwm;

    std::unique_ptr<M80::I2s::II2s> _i2s;
};
