#include "AppFactory.hpp"
#include "AppArena.hpp"
#include "Menu/MenuApplication.hpp"
#include "../M21_Games/Pong.hpp"
#include "../M24_Utilities/AutoRun.hpp"
#include "../M90_Utilities/Assert/Assert.hpp"

AppFactory::Result AppFactory::Create(
    EApplicationId id,
    AppArena& arena,
    Context& context,
    ApplicationsManager& applicationsManager)
{
    switch(id)
    {
        case EApplicationId::Menu:
            return
            {
                new (arena.GetMemory())
                    MenuApplication(
                        context,
                        applicationsManager),

                &DestroyApplication<MenuApplication>
            };

        case EApplicationId::Pong:
            return
            {
                new (arena.GetMemory())
                    Pong(
                        context,
                        applicationsManager),

                &DestroyApplication<Pong>
            };

        case EApplicationId::AutoRun:
            return
            {
                new (arena.GetMemory())
                    AutoRun(
                        context,
                        applicationsManager),

                &DestroyApplication<AutoRun>
            };
    }

    Assert::Fail(
        Types::ETaskId::ApplicationsTask,
        "Unknown app id");

    return {};
}
