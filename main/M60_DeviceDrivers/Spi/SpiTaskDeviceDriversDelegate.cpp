#include "SpiTaskDeviceDriversDelegate.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"

namespace M60::Spi
{
    SpiTaskDeviceDriversDelegate::SpiTaskDeviceDriversDelegate(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log)
    :
        TaskDeviceDriversDelegate(assert, log)
    {
        // No functionality required.
    }

    void SpiTaskDeviceDriversDelegate::Initialize() // NOSONAR: no const to be consequent
    {
        // No actions required.
    }


    void SpiTaskDeviceDriversDelegate::Run() // NOSONAR const TODO
    {
        // NOSONAR TODO SPI
    }
}
