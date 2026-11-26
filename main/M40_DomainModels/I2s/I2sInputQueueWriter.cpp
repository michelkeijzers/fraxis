#include "I2sInputQueueWriter.hpp"
#include "I2sDac/I2sDac.hpp"
#include "I2sMicrophone/I2sMicrophone.hpp"
#include "I2sMixer/I2sMixer.hpp"
#include "../../M30_Messages/I2s/I2sInputQueue.hpp"   
#include "../../M90_Utilities/Log/Log.hpp" 

namespace M90::String
{
    class IStringUtilities;
}

I2sInputQueueWriter::I2sInputQueueWriter(
    I2sInputQueue& i2sInputQueue,
    I2sDac& i2sDac,
    I2sMicrophone& i2sMicrophone,
    I2sMixer& i2sMixer,
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities)
:  
    QueueProcessor(assert, log, stringUtilities),
    _i2sDac(i2sDac),
    _i2sMicrophone(i2sMicrophone),
    _i2sMixer(i2sMixer)
{
    SetQueue(i2sInputQueue);
}

I2sInputQueue& I2sInputQueueWriter::GetI2sInputQueue()
{
    return static_cast<I2sInputQueue&>(GetQueue());
}

void I2sInputQueueWriter::SendMessages()
{
    // TODO
}
