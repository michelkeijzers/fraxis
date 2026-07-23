#include "../L1_Composition/Context/Context.hpp"
#include "../L1_Composition/ComponentsBuilder/EspComponentsBuilder.hpp"
#include "../L2_Applications/ApplicationsManager.hpp"

class Context;

extern "C" void app_main(void)
{
    EspComponentsBuilder espComponentsBuilder;
    Context context;
    espComponentsBuilder.Build(context);

    // ApplicationsManager applicationsManager(
    //     espComponentsBuilder.GetFraxisComponents(), espComponentsBuilder.GetModels(), espComponentsBuilder.GetDrivers());
    // applicationsManager.Initialize();
    // applicationsManager.Run(true);
}
