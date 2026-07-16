#include "LedStripsTask.hpp"
#include "../../Core/Components/LedStrips.hpp"
#include "../../Common/Components/LedStrip/LedStripDriver.hpp"
#include "../../Common/Components/LedStrip/LedStripModel.hpp"
#include "../Messages/Message.hpp"

LedStripsTask::LedStripsTask(RtosTask* rtosTask, 
    RtosQueue& ledStripsQueue,
    ComponentsBuilder::FraxisComponents& fraxisComponents, 
    ComponentsBuilder::Models& models, 
    ComponentsBuilder::Drivers& drivers)
    : _rtosTask(rtosTask), _ledStripsQueue(ledStripsQueue),
      _fraxisComponents(fraxisComponents), _models(models), _drivers(drivers),
      _ledStripsCurrentLimiter(LedStripsCurrentLimiter(MAX_LED_STRIPS_CURRENT_MA))
{
    
    _ledStripsCurrentLimiter.AddLedStripModel(_models.ledStripModel);
}

void LedStripsTask::SetRtosTask(RtosTask* rtosTask)
{
    _rtosTask = rtosTask;
}

void LedStripsTask::Run()
{
    while (true)
    {
        _rtosTask->DelayTask(1);

        Message message;
        if (_ledStripsQueue.Receive(&message, 1))
        {
            switch (message.id)
            {
            case Message::EId::LedStrip_Initialize:
                _drivers.ledStripDriver->Initialize();
                break;

            case Message::EId::LedStrip_BufferReady:
                _drivers.ledStripDriver->Send(
                 _models.ledStripModel->GetInactiveBuffer(), LedStrips::NUMBER_OF_LEDS);
                break;

            default:
                // Ignore others
                break;
            }
        }
    }
}
