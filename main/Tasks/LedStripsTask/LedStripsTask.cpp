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
        // system logic
        _rtosTask->DelayTask(1);

        static uint32_t color = 0;
        color = (color + 5) % 255;

        static uint8_t x = 0;
        x = (x + 10) % 72;
        static uint8_t y = 0;
        y = (y + 1) % 5;

        for (int pixel = 0; pixel < 10; pixel++)
        {
            _fraxisComponents.ledStrips->SetPixel((x + pixel) % 72, (y + pixel) % 5,
                (color + pixel * 10) % 256, (color + pixel * 10 + 50) % 256, (color + pixel * 10 + 100) % 256);
        }

        uint32_t now = _rtosTask->GetTaskTickCount();

        if (now - _lastLedStripsUpdate >= LED_STRIPS_UPDATE_INTERVAL_MS)
        {
            // TODO: add dirty flag
            // TODO: also change Dirty to IDirty 
            // TODO: maybe add another base class for Driver/model if not existing and inheriti  model from IDirty

            _models.ledStripModel->SwapBuffers();
            _ledStripsCurrentLimiter.ApplyGlobalCurrentLimit();
            _drivers.ledStripDriver->Send(_models.ledStripModel->GetInactiveBuffer(), LedStrips::NUMBER_OF_LEDS);
            _lastLedStripsUpdate = now;
        }
    }
}
