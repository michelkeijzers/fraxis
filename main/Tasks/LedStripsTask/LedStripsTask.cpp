#include "LedStripsTask.hpp"
#include "../../Core/Components/LedStrips.hpp"
#include "../../Common/Components/LedStrip/LedStripDriver.hpp"
#include "../../Common/Components/LedStrip/LedStripModel.hpp"

LedStripsTask::LedStripsTask(RtosTask* rtosTask,
    ComponentsBuilder::FraxisComponents& fraxisComponents, 
    ComponentsBuilder::Models& models, 
    ComponentsBuilder::Drivers& drivers)
    : _rtosTask(rtosTask), 
      _fraxisComponents(fraxisComponents), _models(models), _drivers(drivers),
      _ledStripsCurrentLimiter(LedStripsCurrentLimiter(MAX_LED_STRIPS_CURRENT_MA)),
      _lastLedStripsUpdate(0)
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

        uint32_t now = _rtosTask->GetTaskTickCount();

        if (now - _lastLedStripsUpdate >= LED_STRIPS_UPDATE_INTERVAL_MS)
        {
            if (_models.ledStripModel->IsDirty())
            {
                _models.ledStripModel->SwapBuffers();
                _ledStripsCurrentLimiter.ApplyGlobalCurrentLimit();
                _drivers.ledStripDriver->Send(_models.ledStripModel->GetInactiveBuffer(), LedStrips::NUMBER_OF_LEDS);
                _lastLedStripsUpdate = now;
            }
        }
    }
}
