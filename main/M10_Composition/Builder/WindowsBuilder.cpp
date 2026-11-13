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

WindowsBuilder::WindowsBuilder(
    Context& context)
    : Builder(context)
{}

void WindowsBuilder::BuildServicesContext()
{
    ServicesContext& servicesContext = GetContext().GetServices();
    servicesContext.SetRtos(std::make_unique<M81::Rtos::WindowsRtos>());
    servicesContext.SetGpio(std::make_unique<M80::Gpio::WindowsGpio>());
    servicesContext.SetI2c(std::make_unique<M80::I2c::WindowsI2c>());
    servicesContext.SetSpi(std::make_unique<M80::Spi::WindowsSpi>());
    servicesContext.SetRmt(std::make_unique<M80::Rmt::WindowsRmt>());
    servicesContext.SetRandom(std::make_unique<M80::Random::WindowsRandom>());
    servicesContext.SetUart(std::make_unique<M80::Uart::WindowsUart>());
    servicesContext.SetNvs(std::make_unique<M80::Nvs::WindowsNvs>());
    servicesContext.SetPwm(std::make_unique<M80::Pwm::WindowsPwm>());
    servicesContext.SetI2s(std::make_unique<M80::I2s::WindowsI2s>());
}
