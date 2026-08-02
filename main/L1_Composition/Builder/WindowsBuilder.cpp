#include "WindowsBuilder.hpp"

#include "../../L8_Services/Gpio/WindowsGpio.hpp"
#include "../../L8_Services/I2c/WindowsI2c.hpp"
#include "../../L8_Services/Rmt/WindowsRmt.hpp"
#include "../../L8_Services/Rtos/WindowsRtos.hpp"
#include "../../L8_Services/RtosQueue/WindowsRtosQueue.hpp"
#include "../../L8_Services/Random/WindowsRandom.hpp"

WindowsBuilder::WindowsBuilder(
    Context& context)
    : Builder(context)
{}

WindowsBuilder::~WindowsBuilder()
{}

void WindowsBuilder::BuildServicesContext()
{
    GetContext().GetServices().Set(
        std::make_unique<WindowsRtos>(),
        std::make_unique<WindowsGpio>(),
        std::make_unique<WindowsI2c>(),
        std::make_unique<WindowsRmt>(),
        std::make_unique<WindowsRandom>()
    );
}
