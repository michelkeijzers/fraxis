#include "PassiveBuzzerTaskDeviceDriversDelegate.hpp"
#include "../../M10_Composition/Context/Context.hpp"

namespace M60::PassiveBuzzer
{
    PassiveBuzzerTaskDeviceDriversDelegate::PassiveBuzzerTaskDeviceDriversDelegate(
        M90::Assert::IAssert& assert, 
        M90::Log::ILog& log)
    :
        TaskDeviceDriversDelegate(assert, log)
    {
    }

    void PassiveBuzzerTaskDeviceDriversDelegate::Initialize()
    {
        // TODO
    }

    void PassiveBuzzerTaskDeviceDriversDelegate::Run()
    {
        // TODO
    }
}
