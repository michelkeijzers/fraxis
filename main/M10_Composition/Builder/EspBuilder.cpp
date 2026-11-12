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
    GetContext().GetServices().Set(
        std::make_unique<M81::Rtos::EspRtos>(),
        std::make_unique<M80::Gpio::EspGpio>(),
        std::make_unique<M80::I2c::EspI2c>(),
        std::make_unique<M80::Spi::EspSpi>(),
        std::make_unique<M80::Rmt::EspRmt>(),
        std::make_unique<M80::Random::EspRandom>(),
        std::make_unique<M80::Uart::EspUart>(),
        std::make_unique<M80::Nvs::EspNvs>(),
        std::make_unique<M80::Pwm::EspPwm>(),
        std::make_unique<M80::I2s::EspI2s>());
}

#endif // ESP_PLATFORM
