#include "../L1_Composition/Context/Context.hpp"
#include "../L1_Composition/ComponentsBuilder/EspComponentsBuilder.hpp"

#include "../L2_Applications/ApplicationsTask.hpp"

class Context;

extern "C" void app_main(void)
{
    Context context;
    EspComponentsBuilder espComponentsBuilder(context);
    espComponentsBuilder.Build(context);
    context.GetTasks().InitializeAll();
    context.GetDeviceModels().InitializeAll();
    context.GetTasks().StartAll();
}
