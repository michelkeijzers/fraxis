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
#include "../../M80_Services/I2sService/EspI2sService.hpp"
#include "../../M81_RtosServices/Rtos/EspRtos.hpp"

void EspBuilder::BuildServicesContext()
{
    M90::Assert::IAssert& assert = GetContext().GetUtilities().GetAssert();
    
    GetContext().GetServices().SetRtos(std::make_unique<M81::Rtos::EspRtos>(assert));
    GetContext().GetServices().SetGpio(std::make_unique<M80::Gpio::EspGpio>(assert));
    GetContext().GetServices().SetI2c(std::make_unique<M80::I2c::EspI2c>(assert));
    GetContext().GetServices().SetSpi(std::make_unique<M80::Spi::EspSpi>(assert));
    GetContext().GetServices().SetRmt(std::make_unique<M80::Rmt::EspRmt>(assert));
    GetContext().GetServices().SetRandom(std::make_unique<M80::Random::EspRandom>(assert));
    GetContext().GetServices().SetUart(std::make_unique<M80::Uart::EspUart>(assert));
    GetContext().GetServices().SetNvs(std::make_unique<M80::Nvs::EspNvs>(assert));
    GetContext().GetServices().SetPwm(std::make_unique<M80::Pwm::EspPwm>(assert));
    GetContext().GetServices().SetI2sService(std::make_unique<M80::I2s::EspI2sService>(assert));
}

#endif // ESP_PLATFORM
