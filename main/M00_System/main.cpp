#ifdef ESP_PLATFORM

#include "Orchestrator.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M10_Composition/Builder/EspBuilder.hpp"
#include "../M20_Applications/ApplicationsTask.hpp"

class Context;

extern "C" void app_main(
    void)
{
    Context context;
    EspBuilder espBuilder(context);
    Orchestrator orchestrator(espBuilder);
    orchestrator.Initialize();
    orchestrator.StartTasks();
}

#endif // ESP_PLATFORM
