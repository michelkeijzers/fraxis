#include "WindowsBuilder.hpp"

#include "../../M80_Services/Gpio/WindowsGpio.hpp"
#include "../../M80_Services/I2c/WindowsI2c.hpp"
#include "../../M80_Services/Spi/WindowsSpi.hpp"
#include "../../M80_Services/Rmt/WindowsRmt.hpp"
#include "../../M80_Services/Random/WindowsRandom.hpp"
#include "../../M80_Services/Uart/WindowsUart.hpp"
#include "../../M80_Services/Nvs/WindowsNvs.hpp"
#include "../../M80_Services/Pwm/WindowsPwm.hpp"
#include "../../M80_Services/I2s/WindowsI2s.hpp"
#include "../../M81_RtosServices/Rtos/WindowsRtos.hpp"
#include "../../M81_RtosServices/RtosQueue/WindowsRtosQueue.hpp"

void WindowsBuilder::BuildServicesContext()
{
    M90::Assert::IAssert& assert = GetContext().GetUtilities().GetAssert();

    ServicesContext& servicesContext = GetContext().GetServices();
    servicesContext.SetRtos(std::make_unique<M81::Rtos::WindowsRtos>(assert));
    servicesContext.SetGpio(std::make_unique<M80::Gpio::WindowsGpio>(assert));
    servicesContext.SetI2c(std::make_unique<M80::I2c::WindowsI2c>(assert));
    servicesContext.SetSpi(std::make_unique<M80::Spi::WindowsSpi>(assert));
    servicesContext.SetRmt(std::make_unique<M80::Rmt::WindowsRmt>(assert));
    servicesContext.SetRandom(std::make_unique<M80::Random::WindowsRandom>(assert));
    servicesContext.SetUart(std::make_unique<M80::Uart::WindowsUart>(assert));
    servicesContext.SetNvs(std::make_unique<M80::Nvs::WindowsNvs>(assert));
    servicesContext.SetPwm(std::make_unique<M80::Pwm::WindowsPwm>(assert));
    servicesContext.SetI2s(std::make_unique<M80::I2s::WindowsI2s>(assert));
}
