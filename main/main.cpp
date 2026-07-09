#include "Core/TaskManager/TaskManager.hpp"
#include "ESP32/Components/EspComponentsBuilder.hpp"

extern "C" void app_main(void)
{
    EspComponentsBuilder espComponentsBuilder;
    espComponentsBuilder.Build();
    TaskManager taskManager(
        espComponentsBuilder.GetFraxisComponents(), espComponentsBuilder.GetModels(), espComponentsBuilder.GetDrivers());
    taskManager.Initialize();
    taskManager.Run(true);
}
