#include "../M20_Applications/Games/Game.hpp"
#include "../M30_Messages/Types.hpp"
#include "../M80_Services/Random/Random.hpp"
#include <string>

class Pong : public Game
{
public:
    Pong(
        Context& context, 
        ApplicationsManager& applicationsManager);

    void Tick() override;

    void OnJoystickDirectionChanged(
        Types::EJoystickId id, 
        Types::EJoystickDirection direction) override;
    void OnJoystickButtonChanged(
        Types::EJoystickId id, 
        bool state) override;
    void OnSystemButtonChanged(
        bool state) override;

private:
    Random& _random;

    uint32_t _step;
    uint32_t _cpTime;
    uint32_t _player1;
    uint32_t _player2;
};
