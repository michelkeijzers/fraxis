#ifdef ESP_PLATFORM

#include "Orchestrator.hpp"
#include "../L1_Composition/Context/Context.hpp"
#include "../L1_Composition/Builder/EspBuilder.hpp"
#include "../L2_Applications/ApplicationsTask.hpp"

class Context;

extern "C" void app_main(
    void)
{
    Context context;
    EspBuilder espBuilder(context);
    Orchestrator orchestrator(espBuilder);
    orchestrator.Run();
}

#endif // ESP_PLATFORM
