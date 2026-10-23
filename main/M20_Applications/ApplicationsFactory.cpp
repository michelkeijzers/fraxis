#include "ApplicationsFactory.hpp"
#include "ApplicationArena.hpp"
#include "Menu/MenuApplication.hpp"
#include "../M21_Games/Pong.hpp"
#include "../M24_Utilities/AutoRun.hpp"
#include "../M90_Utilities/Assert/Assert.hpp"

ApplicationsFactory::Result ApplicationsFactory::Create(
    EApplicationId id,
    ApplicationArena& arena,
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
        "Unknown application id");

    return {};
}
