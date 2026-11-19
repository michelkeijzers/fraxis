#include "ApplicationsFactory.hpp"
#include "ApplicationArena.hpp"
#include "../M21_Games/Pong.hpp"
#include "../M24_Utilities/AutoRun.hpp"
#include "../M25_Menu/MenuApplication.hpp"
#include "../M90_Utilities/Assert/IAssert.hpp"

ApplicationsFactory::Result ApplicationsFactory::Create(
    EApplicationId id,
    ApplicationArena& arena,
    Context& context,
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities,
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
                        stringUtilities,
                        applicationsManager),

                &DestroyApplication<Pong>
            };

        case EApplicationId::AutoRun:
            return
            {
                new (arena.GetMemory().data())
                    AutoRun(
                        context,
                        stringUtilities,
                        applicationsManager),

                &DestroyApplication<AutoRun>
            };

        default:
            assert.Fail(Types::ETaskId::ApplicationsTask, "Illegal EApplicationId");
    }

    return { nullptr, nullptr };
}
