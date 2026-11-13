#ifdef ESP_PLATFORM

#include "EspBuilder.hpp"

#include "../../M80_Services/Gpio/EspGpio.hpp"
#include "../../M80_Services/I2c/EspI2c.hpp"
#include "../../M80_Services/Spi/EspSpi.hpp"
#include "../../M80_Services/Rmt/EspRmt.hpp"
#include "../../M81_RtosServices/Rtos/EspRtos.hpp"
#include "../../M81_RtosServices/RtosQueue/EspRtosQueue.hpp"
#include "../../M80_Services/Random/EspRandom.hpp"
#include "../../M80_Services/Uart/EspUart.hpp"
#include "../../M80_Services/Nvs/EspNvs.hpp"
#include "../../M80_Services/Pwm/EspPwm.hpp"
#include "../../M80_Services/I2s/EspI2s.hpp"
#include "../../M81_RtosServices/Rtos/EspRtos.hpp"

EspBuilder::EspBuilder(
    Context& context)
: Builder(context) 
{
}

void EspBuilder::BuildServicesContext()
{
    GetContext().GetServices().SetRtos(std::make_unique<M81::Rtos::EspRtos>());
    GetContext().GetServices().SetGpio(std::make_unique<M80::Gpio::EspGpio>());
    GetContext().GetServices().SetI2c(std::make_unique<M80::I2c::EspI2c>());
    GetContext().GetServices().SetSpi(std::make_unique<M80::Spi::EspSpi>());
    GetContext().GetServices().SetRmt(std::make_unique<M80::Rmt::EspRmt>());
    GetContext().GetServices().SetRandom(std::make_unique<M80::Random::EspRandom>());
    GetContext().GetServices().SetUart(std::make_unique<M80::Uart::EspUart>());
    GetContext().GetServices().SetNvs(std::make_unique<M80::Nvs::EspNvs>());
    GetContext().GetServices().SetPwm(std::make_unique<M80::Pwm::EspPwm>());
    GetContext().GetServices().SetI2s(std::make_unique<M80::I2s::EspI2s>());
}

#endif // ESP_PLATFORM
