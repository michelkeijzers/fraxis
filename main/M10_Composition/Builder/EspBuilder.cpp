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
#include "../../M80_Services/I2s/EspI2sService.hpp"
#include "../../M81_RtosServices/Rtos/EspRtos.hpp"

void EspBuilder::BuildServicesContext()
{
    M90::Assert::IAssert& assert = GetContext().GetUtilities().GetAssert();
    
    auto& services = GetContext().GetServices();
    services.SetRtos(std::make_unique<M81::Rtos::EspRtos>(assert));
    services.SetGpio(std::make_unique<M80::Gpio::EspGpio>(assert));
    services.SetI2c(std::make_unique<M80::I2c::EspI2c>(assert));
    services.SetSpi(std::make_unique<M80::Spi::EspSpi>(assert));
    services.SetRmt(std::make_unique<M80::Rmt::EspRmt>(assert));
    services.SetRandom(std::make_unique<M80::Random::EspRandom>(assert));
    services.SetUart(std::make_unique<M80::Uart::EspUart>(assert));
    services.SetNvs(std::make_unique<M80::Nvs::EspNvs>(assert));
    services.SetPwm(std::make_unique<M80::Pwm::EspPwm>(assert));
    services.SetI2sService(std::make_unique<M80::I2s::EspI2sService>(assert));
}

#endif // ESP_PLATFORM
