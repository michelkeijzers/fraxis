#include "ApplicationsFactory.hpp"
#include "ApplicationArena.hpp"
#include "../M21_Games/Pong.hpp"
#include "../M24_Utilities/AutoRun.hpp"
#include "../M25_Menu/MenuApplication.hpp"
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
            // Menu always stays loaded.
            break;

        case EApplicationId::Pong:
            return
            {
                new (arena.GetMemory().data())
                    Pong(
                        context,
                        applicationsManager),

                &DestroyApplication<Pong>
            };

        case EApplicationId::AutoRun:
            return
            {
                new (arena.GetMemory().data())
                    AutoRun(
                        context,
                        applicationsManager),

                &DestroyApplication<AutoRun>
            };

        default:
            Assert::Fail(Types::ETaskId::ApplicationsTask, "Illegal EApplicationId");
    }

    Assert::Fail(
        Types::ETaskId::ApplicationsTask,
        "Unknown application id");

    return {};
}
