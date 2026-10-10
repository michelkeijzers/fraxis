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
        std::make_unique<WindowsRtos>(),
        std::make_unique<WindowsGpio>(),
        std::make_unique<WindowsI2c>(),
        std::make_unique<WindowsSpi>(),
        std::make_unique<WindowsRmt>(),
        std::make_unique<WindowsRandom>(),
        std::make_unique<WindowsUart>(),
        std::make_unique<WindowsNvs>(),
        std::make_unique<WindowsPwm>(),
        std::make_unique<WindowsI2s>());
}
