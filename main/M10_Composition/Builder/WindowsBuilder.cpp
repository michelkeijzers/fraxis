#include "WindowsBuilder.hpp"

#include "../../M80_Services/Gpio/WindowsGpio.hpp"
#include "../../M80_Services/I2c/WindowsI2c.hpp"
#include "../../M80_Services/Rmt/WindowsRmt.hpp"
#include "../../M80_Services/Rtos/WindowsRtos.hpp"
#include "../../M80_Services/RtosQueue/WindowsRtosQueue.hpp"
#include "../../M80_Services/Random/WindowsRandom.hpp"
#include "../../M80_Services/Uart/WindowsUart.hpp"

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
        std::make_unique<WindowsRmt>(),
        std::make_unique<WindowsRandom>(), 
        std::make_unique<WindowsUart>()
    );
}
