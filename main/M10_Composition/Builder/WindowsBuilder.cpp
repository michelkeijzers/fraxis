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
    GetContext().GetServices().Set(
        std::make_unique<M81::Rtos::WindowsRtos>(),
        std::make_unique<M80::Gpio::WindowsGpio>(),
        std::make_unique<M80::I2c::WindowsI2c>(),
        std::make_unique<M80::Spi::WindowsSpi>(),
        std::make_unique<M80::Rmt::WindowsRmt>(),
        std::make_unique<M80::Random::WindowsRandom>(),
        std::make_unique<M80::Uart::WindowsUart>(),
        std::make_unique<M80::Nvs::WindowsNvs>(),
        std::make_unique<M80::Pwm::WindowsPwm>(),
        std::make_unique<M80::I2s::WindowsI2s>());
}
